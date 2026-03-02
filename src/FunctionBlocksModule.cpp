#include "FunctionBlocksModule.h"
#include "FunctionBlocks/BayesianBinarySensorBlock.h"
#include "FunctionBlocks/BlinkerBlock.h"
#include "FunctionBlocks/CountDownBlock.h"
#include "FunctionBlocks/LogicFunctionBlock.h"
#include "FunctionBlocks/PrioritySwitchFunctionBlock.h"
#include "FunctionBlocks/SelectionBlock.h"
#include "FunctionBlocks/SimpleAggregationBlock.h"
#include "FunctionBlocks/TextFormatBlock.h"
#include "FunctionBlocks/ValueMonitorBlock.h"
#include "knxprod.h"

#define OPENKNX_LEDFUNC_FCB_TIME_SIGNAL 400

FunctionBlocksModule::FunctionBlocksModule()
{
}

const std::string FunctionBlocksModule::name()
{
    return "FunctionBlocks";
}

void FunctionBlocksModule::showInformations()
{
}

const std::string FunctionBlocksModule::version()
{
#ifdef MODULE_FunctionBlocks_Version
    return MODULE_FunctionBlocks_Version;
#else
    // hides the module in the version output on the console, because the firmware version is sufficient.
    return "";
#endif
}

void FunctionBlocksModule::setup(bool configured)
{
    Module::setup(configured);
    FCBChannelOwnerModule::initialize(configured ? ParamFCB_VisibleChannels : 0);
    FCBChannelOwnerModule::setup(configured);
    _startTime = millis();
#if OPENKNX_LEDFUNC_BASE_PROG_UNCONFIGUREDSUPPORT
    _ledProgLedFunctionGroup = openknx.ledFunctions.get(OPENKNX_LEDFUNC_BASE_PROG);
    _dummyLed = new DummyLedToGetCurrentState();
    _dummyLed->init();
    openknx.ledFunctions.assignLed2Function(_dummyLed, OPENKNX_LEDFUNC_BASE_PROG);
#endif
}

void FunctionBlocksModule::showHelp()
{
}

bool FunctionBlocksModule::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd.rfind("fb", 0) == 0)
    {
        auto channelString = cmd.substr(2);
        if (channelString.length() > 0)
        {
            auto pos = channelString.find_first_of(' ');
            std::string channelNumberString;
            std::string channelCmd;
            if (pos > 0 && pos != std::string::npos)
            {
                channelNumberString = channelString.substr(0, pos);
                channelCmd = channelString.substr(pos + 1);
            }
            else
            {
                channelNumberString = channelString;
                channelCmd = "";
            }
            auto channel = atoi(channelNumberString.c_str());
            if (channel < 1 || channel > getNumberOfChannels())
            {
                logInfoP("Channel %d not found", channel);
                return true;
           } 
            FunctionBlock* functionBlock = (FunctionBlock*)getChannel(channel - 1);
            if (functionBlock != nullptr)
            {
                if (functionBlock->processCommand(channelCmd, diagnoseKo))
                    return true;
            }
        }
    }
    return false;
}

OpenKNX::Channel* FunctionBlocksModule::createChannel(uint8_t _channelIndex)
{

    if (ParamFCB_CHChannelDisabled)
    {
        logDebugP("Channel %d is disabled", _channelIndex);
        return nullptr;
    }
    // <Enumeration Id="%ENID%" Value="0"  Text="Deaktiviert"                    />
    // <Enumeration Id="%ENID%" Value="1"  Text="UND"                            />
    // <Enumeration Id="%ENID%" Value="2"  Text="ODER"                           />
    // <Enumeration Id="%ENID%" Value="4"  Text="Anzahl"                         />
    // <Enumeration Id="%ENID%" Value="8"  Text="Auswahl (Multiplexer)"          />
    // <Enumeration Id="%ENID%" Value="3"  Text="Prioritätsschalter"             />
    // <Enumeration Id="%ENID%" Value="5"  Text="Statistische Aggregation"       />
    // <Enumeration Id="%ENID%" Value="7"  Text="Wertüberwachung"                />
    // <Enumeration Id="%ENID%" Value="6"  Text="Count Down Zeitgeber"           />
    // <Enumeration Id="%ENID%" Value="9"  Text="Blinker"                        />
    // <Enumeration Id="%ENID%" Value="10" Text="Bayesian Binary Sensor"         />
    // <Enumeration Id="%ENID%" Value="11" Text="Text Format"                     />
    switch (ParamFCB_CHChannelType)
    {
        case 0:
            logDebugP("Channel %d is deactivated", _channelIndex);
            return nullptr;
        case 1:
            return new LogicFunctionBlock(_channelIndex, LogicFunctionBlockType::LogicAND);
        case 2:
            return new LogicFunctionBlock(_channelIndex, LogicFunctionBlockType::LogicOR);
        case 4:
            return new LogicFunctionBlock(_channelIndex, LogicFunctionBlockType::LogicCOUNT);
        case 3:
            return new PrioritySwitchFunctionBlock(_channelIndex);
        case 5:
            return new SimpleAggregationBlock(_channelIndex, static_cast<SimpleAggregationBlockType>(ParamFCB_CHAggType));
        case 6:
            return new CountDownBlock(_channelIndex);
        case 7:
            return new ValueMonitorBlock(_channelIndex);
        case 8:
            return new SelectionBlock(_channelIndex);
        case 9:
            return new BlinkerBlock(_channelIndex);
        case 10:
            return new BayesianBinarySensorBlock(_channelIndex);
        case 11:
            return new TextFormatBlock(_channelIndex);
        default:
            logErrorP("Unknown channel type %d", ParamFCB_CHChannelType);
            return nullptr;
    }
}

void FunctionBlocksModule::loop(bool configured)
{
    if (configured && _startTime != 0 && millis() - _startTime > 3000)
    {
        _startTime = 0;
        for (uint8_t i = 0; i < getNumberOfChannels(); i++)
        {
            FunctionBlock* functionBlock = (FunctionBlock*)getChannel(i);
            if (functionBlock != nullptr)
            {
                functionBlock->initMissingInputValues();
            }
        }
    }
    FCBChannelOwnerModule::loop(configured);
    _statusLedTimeStateSeconds.loop();
    _statusLedValueMonitor.loop();
#if OPENKNX_LEDFUNC_BASE_PROG_UNCONFIGUREDSUPPORT
    if (!configured)
    {
        if (knx.progMode())
        {
            _ledProgLedFunctionGroup->color(OpenKNX::Led::Color::Red);
            _ledProgLedFunctionGroup->on();
            _blinkState = 0;
        }
        else
        {
            switch (_blinkState)
            {
                case 0:
                    if (_dummyLed->isOff)
                    {
                        if (millis() - _dummyLed->progLedLastOff >= 3000)
                        {
                            _blinkState = 1;
                            _ledProgLedFunctionGroup->color(OpenKNX::Led::Color::Orange);
                            _ledProgLedFunctionGroup->on();
                            _lastBlink = millis();
                        }
                    }
                    break;
                case 1:
                    if (millis() - _lastBlink >= 50)
                    {
                        _ledProgLedFunctionGroup->off();
                        _dummyLed->progLedLastOff = millis();
                        if (knx.individualAddress() == 0xFFFF)
                        {
                            _blinkState = 2;
                            _lastBlink = millis();
                        }
                        else
                        {
                            _blinkState = 0;
                        }
                    }
                    break;
                case 2:
                    if (millis() - _lastBlink >= 50)
                    {
                        _ledProgLedFunctionGroup->color(OpenKNX::Led::Color::Orange);
                        _ledProgLedFunctionGroup->on();
                        _lastBlink = millis();
                        _blinkState = 3;
                    }
                    break;
                case 3:
                    if (millis() - _lastBlink >= 50)
                    {
                        _ledProgLedFunctionGroup->off();
                        _dummyLed->progLedLastOff = millis();
                        _blinkState = 0;
                    }
                    break;
            }
        }
    }
#endif
}

FunctionBlocksModule openknxFunctionBlocksModule;