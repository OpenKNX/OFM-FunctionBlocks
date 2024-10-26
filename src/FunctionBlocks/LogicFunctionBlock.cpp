#include "LogicFunctionBlock.h"
#include "knxprod.h"

LogicFunctionBlock::LogicFunctionBlock(uint8_t channelIndex, LogicFunctionBlockType type)
    : FunctionBlock(channelIndex, type == LogicFunctionBlockType::LogicOR ? "OR" : "AND"),
      _type(type)
{
}

uint8_t LogicFunctionBlock::getParamInput(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHLogicKo0D;
        case 1:
            return ParamFCB_CHLogicKo1D;
        case 2:
            return ParamFCB_CHLogicKo2D;
        case 3:
            return ParamFCB_CHLogicKo3D;
        case 4:
            return ParamFCB_CHLogicKo4D;
        case 5:
            return ParamFCB_CHLogicKo5D;
        case 6:
            return ParamFCB_CHLogicKo6D;
        case 7:
            return ParamFCB_CHLogicKo7D;
        case 8:
            return ParamFCB_CHLogicKo8D;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

uint8_t LogicFunctionBlock::getParamInputBehavior(uint8_t input)
{
    switch (input)
    {
        case 0:
            return ParamFCB_CHLogicBehavKo0;
        case 1:
            return ParamFCB_CHLogicBehavKo1;
        case 2:
            return ParamFCB_CHLogicBehavKo2;
        case 3:
            return ParamFCB_CHLogicBehavKo3;
        case 4:
            return ParamFCB_CHLogicBehavKo4;
        case 5:
            return ParamFCB_CHLogicBehavKo5;
        case 6:
            return ParamFCB_CHLogicBehavKo6;
        case 7:
            return ParamFCB_CHLogicBehavKo7;
        case 8:
            return ParamFCB_CHLogicBehavKo8;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

void LogicFunctionBlock::readInputKos()
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

void LogicFunctionBlock::initMissingInputValues()
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
        }
    }
}

void LogicFunctionBlock::handleKo(GroupObject& ko)
{
    auto index = FCB_KoCalcIndex(ko.asap());
    if (index >= FCB_KoCHKO0 && index <= FCB_KoCHKO8)
    {
        // Recalc the output
        bool result = (_type == LogicFunctionBlockType::LogicAND ? true : false);
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
                return;
            }
            auto& ko = getKo(i);

            auto inputValue = (bool)ko.value(DPT_Switch);
            if (inputKo == 2)
                inputValue = !inputValue;
            if (_type == LogicFunctionBlockType::LogicAND)
            {
                if (!inputValue)
                {
                    result = false;
                    break;
                }
            }
            else
            {
                if (inputValue)
                {
                    result = true;
                    break;
                }
            }
        }
        if (ParamFCB_CHLogicOutInv)
            result = !result;
     
        // <Enumeration Text="Bei jedem Eingangstelegram" Value="0" Id="%ENID%" />
        // <Enumeration Text="Nur bei Änderung des Ausgangswertes" Value="1" Id="%ENID%" />
        if (ParamFCB_CHLogicBehavOut)
            KoFCB_CHKO9.valueCompare(result, DPT_Switch);
        else
            KoFCB_CHKO9.value(result, DPT_Switch);
    }
}