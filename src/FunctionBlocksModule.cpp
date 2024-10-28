#include "FunctionBlocksModule.h"
#include "knxprod.h"
#include "FunctionBlocks/LogicFunctionBlock.h"
#include "FunctionBlocks/PrioritySwitchFunctionBlock.h"
#include "FunctionBlocks/SimpleAggregationBlock.h"

FunctionBlocksModule::FunctionBlocksModule()
{

}

const std::string FunctionBlocksModule::name()
{
    return "FunctionBlocks";
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
    return false;
}

OpenKNX::Channel* FunctionBlocksModule::createChannel(uint8_t _channelIndex)
{

    if (ParamFCB_CHChannelDisabled)
    {
        logDebugP("Channel %d is disabled", _channelIndex);
        return nullptr;
    }
    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="UND" Value="1" Id="%ENID%" />
    // <Enumeration Text="ODER" Value="2" Id="%ENID%" />
    // <Enumeration Text="Prioritätsschalter" Value="3" Id="%ENID%" />
    // <Enumeration Text="Anzahl" Value="4" Id="%ENID%" />
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
            FunctionBlock* functionBlock = (FunctionBlock*) getChannel(i);
            if (functionBlock != nullptr)
            {
                functionBlock->initMissingInputValues();
            }
        }
    }
    FCBChannelOwnerModule::loop();
}

FunctionBlocksModule openknxFunctionBlocksModule;