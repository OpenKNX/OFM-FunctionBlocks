#include "PrioritySwitchFunctionBlock.h"

PrioritySwitchFunctionBlock::PrioritySwitchFunctionBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "PrioritySwitch")
{
}

byte PrioritySwitchFunctionBlock::getParamInput(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHPrioKo0D;
        case 1:
            return ParamFCB_CHPrioKo1D;
        case 2:
            return ParamFCB_CHPrioKo2D;
        case 3:
            return ParamFCB_CHPrioKo3D;
        case 4:
            return ParamFCB_CHPrioKo4D;
        case 5:
            return ParamFCB_CHPrioKo5D;
        case 6:
            return ParamFCB_CHPrioKo6D;
        case 7:
            return ParamFCB_CHPrioKo7D;
        case 8:
            return ParamFCB_CHPrioKo8D;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

uint8_t PrioritySwitchFunctionBlock::getParamInputBehavior(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHPrioBehavKo0;
        case 1:
            return ParamFCB_CHPrioBehavKo1;
        case 2:
            return ParamFCB_CHPrioBehavKo2;
        case 3:
            return ParamFCB_CHPrioBehavKo3;
        case 4:
            return ParamFCB_CHPrioBehavKo4;
        case 5:
            return ParamFCB_CHPrioBehavKo5;
        case 6:
            return ParamFCB_CHPrioBehavKo6;
        case 7:
            return ParamFCB_CHPrioBehavKo7;
        case 8:
            return ParamFCB_CHPrioBehavKo8;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

uint8_t PrioritySwitchFunctionBlock::getParamOutByte(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHPrioOutByteKo0;
        case 1:
            return ParamFCB_CHPrioOutByteKo1;
        case 2:
            return ParamFCB_CHPrioOutByteKo2;
        case 3:
            return ParamFCB_CHPrioOutByteKo3;
        case 4:
            return ParamFCB_CHPrioOutByteKo4;
        case 5:
            return ParamFCB_CHPrioOutByteKo5;
        case 6:
            return ParamFCB_CHPrioOutByteKo6;
        case 7:
            return ParamFCB_CHPrioOutByteKo7;
        case 8:
            return ParamFCB_CHPrioOutByteKo8;
        case 255:
            return ParamFCB_CHPrioOutByteDefault;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

uint8_t PrioritySwitchFunctionBlock::getParamOutPercent(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHPrioOutPKo0;
        case 1:
            return ParamFCB_CHPrioOutPKo1;
        case 2:
            return ParamFCB_CHPrioOutPKo2;
        case 3:
            return ParamFCB_CHPrioOutPKo3;
        case 4:
            return ParamFCB_CHPrioOutPKo4;
        case 5:
            return ParamFCB_CHPrioOutPKo5;
        case 6:
            return ParamFCB_CHPrioOutPKo6;
        case 7:
            return ParamFCB_CHPrioOutPKo7;
        case 8:
            return ParamFCB_CHPrioOutPKo8;
        case 255:
            return ParamFCB_CHPrioOutPDefault;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

void PrioritySwitchFunctionBlock::readInputKos()
{
    for (uint8_t i = 0; i < 9; i++)
    {
        // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Normal" Value="1" Id="%ENID%" />
        // <Enumeration Text="Invertiert" Value="2" Id="%ENID%" />
        auto inputKo = getParamInput(i);
        if (inputKo == 0)
            continue;

        auto& ko = getKo(i);
        // <Enumeration Text="AUS" Value="0" Id="%ENID%" />
        // <Enumeration Text="EIN" Value="1" Id="%ENID%" />
        // <Enumeration Text="von Bus lesen, dann AUS" Value="3" Id="%ENID%" />
        // <Enumeration Text="von Bus lesen, dann EIN" Value="4" Id="%ENID%" />
        auto inputBehavior = getParamInputBehavior(i);
        switch (inputBehavior)
        {
            case 0:
                ko.value(false, DPT_Switch);
                break;
            case 1:
                ko.value(true, DPT_Switch);
                break;
            case 2:
            case 3:
                ko.requestObjectRead();
                break;
        }
    }
}

void PrioritySwitchFunctionBlock::initMissingInputValues()
{
    for (uint8_t i = 0; i < 9; i++)
    {
        // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Normal" Value="1" Id="%ENID%" />
        // <Enumeration Text="Invertiert" Value="2" Id="%ENID%" />
        auto inputKo = getParamInput(i);
        if (inputKo == 0)
            continue;

        if (!hasValue(i))
        {
            auto& ko = getKo(i);
            auto inputBehavior = getParamInputBehavior(i);
            switch (inputBehavior)
            {
                case 2:
                    ko.value(false, DPT_Switch);
                    break;
                case 3:
                    ko.value(true, DPT_Switch);
                    break;
            }
            processInputKo(ko);
        }
    }
}

void PrioritySwitchFunctionBlock::handleKo(GroupObject& ko)
{
    auto index = FCB_KoCalcIndex(ko.asap());
    if (index >= FCB_KoCHKO0 && index <= FCB_KoCHKO8)
    {
        // Recalc the output
        uint8_t prio = 255;
        for (uint8_t i = 0; i < 9; i++)
        {
            // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
            // <Enumeration Text="Normal" Value="1" Id="%ENID%" />
            // <Enumeration Text="Invertiert" Value="2" Id="%ENID%" />
            auto inputKo = getParamInput(i);
            if (inputKo == 0)
                continue;
       
            if (!hasValue(i))
                return;

            auto& ko = getKo(i);

            auto inputValue = (bool)ko.value(DPT_Switch);
            if (inputKo == 2)
                inputValue = !inputValue;
            if (inputValue)
            {
                prio = i;
                break;
            }
        }
        setOutputForPrio(prio);
    }
}

void PrioritySwitchFunctionBlock::setOutputForPrio(uint8_t input)
{
    // <Enumeration Text="Prozent" Value="0" Id="%ENID%" />
    // <Enumeration Text="1 Byte (Ohne Vorzeichen)" Value="1" Id="%ENID%" />
    auto outputType = ParamFCB_CHPrioOutputType;
    uint8_t result = outputType ? getParamOutByte(input) : getParamOutPercent(input);
    
    // <Enumeration Text="Bei jedem Eingangstelegram" Value="0" Id="%ENID%" />
    // <Enumeration Text="Nur bei Änderung des Ausgangswertes" Value="1" Id="%ENID%" />
    if (ParamFCB_CHPrioBehavOut && KoFCB_CHKO9.initialized())
        KoFCB_CHKO9.valueCompare(result, outputType ?  DPT_Value_1_Count : DPT_Scaling);
    else
        KoFCB_CHKO9.value(result, outputType ? DPT_Value_1_Count : DPT_Scaling);
}