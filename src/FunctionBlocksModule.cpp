#include "FunctionBlocksModule.h"
#include "FunctionBlocks/CountDownBlock.h"
#include "FunctionBlocks/LogicFunctionBlock.h"
#include "FunctionBlocks/PrioritySwitchFunctionBlock.h"
#include "FunctionBlocks/SimpleAggregationBlock.h"
#include "knxprod.h"

FunctionBlocksModule::FunctionBlocksModule()
{
}

const std::string FunctionBlocksModule::name()
{
    return "FunctionBlocks";
}

void FunctionBlocksModule::showInformations()
{
#ifdef MODULE_FunctionBlocks_Version
    openknx.logger.logWithPrefixAndValues(logPrefix(), "Function Blocks %s", MODULE_FunctionBlocks_Version);
#else
    openknx.logger.logWithPrefix(logPrefix(), "Function Blocks");
#endif  
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
    FCBChannelOwnerModule::initialize(ParamFCB_VisibleChannels);
    FCBChannelOwnerModule::setup(configured);
    _startTime = millis();
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
    // <Enumeration Id="%ENID%" Value="3"  Text="Prioritätsschalter"             />
    // <Enumeration Id="%ENID%" Value="4"  Text="Anzahl"                         />
    // <Enumeration Id="%ENID%" Value="5"  Text="Statistische Aggregation"       />
    // <Enumeration Id="%ENID%" Value="6"  Text="Count Down Zeitgeber"           />
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
        default:
            logErrorP("Unknown channel type %d", ParamFCB_CHChannelType);
            return nullptr;
    }
}

void FunctionBlocksModule::loop()
{
    if (_startTime != 0 && millis() - _startTime > 3000)
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
    FCBChannelOwnerModule::loop();
}

FunctionBlocksModule openknxFunctionBlocksModule;