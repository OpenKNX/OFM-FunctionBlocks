#include "SimpleAggregationBlock.h"
#include "knxprod.h"

#define TYPE2Str(type)                                                                                            \
    type == SimpleAggregationBlockType::AggrSUM ? "SUM" : type == SimpleAggregationBlockType::AggrAVG  ? "AVG"    \
                                                      : type == SimpleAggregationBlockType::AggrMIN    ? "MIN"    \
                                                      : type == SimpleAggregationBlockType::AggrMAX    ? "MAX"    \
                                                      : "Width"
                                                      /*
                                                      : type == SimpleAggregationBlockType::AggrWidth  ? "Width"  \
                                                      : type == SimpleAggregationBlockType::AggrMedian ? "Median" \
                                                      : type == SimpleAggregationBlockType::AggrQ25    ? "Q25"    \
                                                      : type == SimpleAggregationBlockType::AggrQ75    ? "Q75"    \
                                                                                                       : "STD"
                                                      */

#define FCB_LIMIT(t, x, min, max)  \
    if (((t)(x)) < ((t)(min)))                \
        x = ((t)(min));                \
    else if (((t)(x)) > ((t)(max)))           \
        x = ((t)(max));

SimpleAggregationBlock::SimpleAggregationBlock(uint8_t channelIndex, SimpleAggregationBlockType type)
    : FunctionBlock(channelIndex, TYPE2Str(type)),
      _type(type)
{
}

uint8_t SimpleAggregationBlock::getParamInput(uint8_t input)
{
    logDebugP("getParamInput(%d)", input);
    switch (input)
    {
        case 0:
            return ParamFCB_CHAggKo0D;
        case 1:
            return ParamFCB_CHAggKo1D;
        case 2:
            return ParamFCB_CHAggKo2D;
        case 3:
            return ParamFCB_CHAggKo3D;
        case 4:
            return ParamFCB_CHAggKo4D;
        case 5:
            return ParamFCB_CHAggKo5D;
        case 6:
            return ParamFCB_CHAggKo6D;
        case 7:
            return ParamFCB_CHAggKo7D;
        case 8:
            return ParamFCB_CHAggKo8D;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

/*
uint8_t SimpleAggregationBlock::getParamInputBehavior(uint8_t input)
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
*/

void SimpleAggregationBlock::readInputKos()
{
/*
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
*/
}

void SimpleAggregationBlock::initMissingInputValues()
{
/*
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
*/
}

void SimpleAggregationBlock::handleKo(GroupObject& ko)
{
    auto index = FCB_KoCalcIndex(ko.asap());
    if (index >= FCB_KoCHKO0 && index <= FCB_KoCHKO8)
    {
        logDebugP("handleKo: %d; %d; %d", index, ParamFCB_CHAggInputDpt, ParamFCB_CHAggOutputDptEff);

		// <Enumeration Text="5.*           8-Bit vorzeichenlos"              Value="50"   Id="%ENID%" />
		// <Enumeration Text="5.001       Prozent (0..100%)"                  Value="51"   Id="%ENID%" />
		// <Enumeration Text="6.*           8-Bit vorzeichenbehaftet"         Value="61"   Id="%ENID%" />
		// <Enumeration Text="7.*           2-Byte vorzeichenlos"             Value="70"   Id="%ENID%" />
		// <Enumeration Text="8.*           2-Byte vorzeichenbehaftet"        Value="80"   Id="%ENID%" />
		// <Enumeration Text="9.*           2-Byte Gleitkommawert"            Value="90"   Id="%ENID%" />
		// <Enumeration Text="12.*         4-Byte vorzeichenlos"             Value="120"   Id="%ENID%" />
		// <Enumeration Text="13.*         4-Byte vorzeichenbehaftet"        Value="130"   Id="%ENID%" />
		// <Enumeration Text="14.*         4-Byte Gleitkommawert"            Value="140"   Id="%ENID%" />
        Dpt dptInput = DPT_Switch;
        switch (ParamFCB_CHAggInputDpt)
        {
            case 50:
                dptInput = DPT_Value_1_Ucount;
                break;
            case 51:
                dptInput = DPT_Scaling;
                break;
            case 61:
                dptInput = DPT_Value_1_Count;
                break;
            case 70:
                dptInput = DPT_Value_2_Ucount;
                break;
            case 80:
                dptInput = DPT_Value_2_Count;
                break;
            case 90:
                dptInput = DPT_Value_Temp;
                break;
            case 120:
                dptInput = DPT_Value_4_Ucount;
                break;
            case 130:
                dptInput = DPT_Value_4_Count;
                break;
            case 140:
                dptInput = DPT_Value_Amplitude;
                break;
            default:
                break;
        }
        Dpt dptOutput = DPT_Switch;
        switch (ParamFCB_CHAggOutputDptEff)
        {
            case 50:
                dptOutput = DPT_Value_1_Ucount;
                break;
            case 51:
                dptOutput = DPT_Scaling;
                break;
            case 61:
                dptOutput = DPT_Value_1_Count;
                break;
            case 70:
                dptOutput = DPT_Value_2_Ucount;
                break;
            case 80:
                dptOutput = DPT_Value_2_Count;
                break;
            case 90:
                dptOutput = DPT_Value_Temp;
                break;
            case 120:
                dptOutput = DPT_Value_4_Ucount;
                break;
            case 130:
                dptOutput = DPT_Value_4_Count;
                break;
            case 140:
                dptOutput = DPT_Value_Amplitude;
                break;
            default:
                break;
        }
        const bool intOutput = (dptOutput.mainGroup != 9) && (dptOutput.mainGroup != 14);

        // Recalc the output
        double min = std::numeric_limits<double>::max();
        double max = std::numeric_limits<double>::min();
        double sum = 0.0;
        uint8_t count = 0;
        for (uint8_t i = 0; i < 9; i++)
        {
            // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
            // <Enumeration Text="Aktiv" Value="1" Id="%ENID%" />
            auto inputKo = getParamInput(i);
            logDebugP("  input(%d) inputKo: %d", i, inputKo);
            if (inputKo == 0)
            {
                continue;
            }

            if (!hasValue(i))
            {
                // TODO handling of incomplete input values; current implementation requires all
                logDebugP("  input(%d) NOT has value", i);
                return;
            }

            const double inputValue = getKo(i).value(dptInput);

            switch (_type)
            {
                case SimpleAggregationBlockType::AggrMIN:
                case SimpleAggregationBlockType::AggrMAX:
                case SimpleAggregationBlockType::AggrWidth:
                    min = MIN(min, inputValue);
                    max = MAX(max, inputValue);
                    break;
                /*
                case SimpleAggregationBlockType::AggrMedian:
                case SimpleAggregationBlockType::AggrQ25:
                case SimpleAggregationBlockType::AggrQ75:
                case SimpleAggregationBlockType::AggrSTD:
                */
                case SimpleAggregationBlockType::AggrSUM:
                case SimpleAggregationBlockType::AggrAVG:
                default:
                    sum += inputValue;
                    break;
            }

            count++;
        }

        logDebugP("  count %d", count);
        if (count == 0)
        {
            return;
        }

        KNXValue result = 0.0;
        switch (_type)
        {
            case SimpleAggregationBlockType::AggrSUM:
                result = sum;
                break;
            case SimpleAggregationBlockType::AggrAVG:
                result = sum / count;
                break;
            case SimpleAggregationBlockType::AggrMIN:
                result = min;
                break;
            case SimpleAggregationBlockType::AggrMAX:
                result = max;
                break;
            case SimpleAggregationBlockType::AggrWidth:
                result = max - min;
                break;
            /*
            case SimpleAggregationBlockType::AggrMedian:
            case SimpleAggregationBlockType::AggrQ25:
            case SimpleAggregationBlockType::AggrQ75:
            case SimpleAggregationBlockType::AggrSTD:
            */
            default:
                break;
        }
        logDebugP("  result %f (of type %d)", result, _type);

        if (ParamFCB_CHAggOutputRounding)
        {
            result = (int64_t)round((double)result);
        }
        else if (intOutput)
        {
            result = (int64_t)result;
        }

        if (ParamFCB_CHAggOutputOverflow == 1)
        {
            _limitToOutputDptRange(result);
        }

        // <Enumeration Text="Bei jedem Eingangstelegram" Value="0" Id="%ENID%" />
        // <Enumeration Text="Nur bei Änderung des Ausgangswertes" Value="1" Id="%ENID%" />
        if (ParamFCB_CHAggBehavOut)
        {
            KoFCB_CHKO9.valueCompare(result, dptOutput);
        }
        else
        {
            KoFCB_CHKO9.value(result, dptOutput);
        }
    }
}

void SimpleAggregationBlock::_limitToOutputDptRange(KNXValue& result)
{
    switch (ParamFCB_CHAggOutputDptEff)
    {
        case 50: 
            FCB_LIMIT(int64_t, result, 0, 255)
            break;
        case 51:
            FCB_LIMIT(int64_t, result, 0, 100)
            break;
        case 61:
            FCB_LIMIT(int64_t, result, -128, 128)
            break;
        case 70:
            FCB_LIMIT(int64_t, result, 0, 65535)
            break;
        case 80:
            FCB_LIMIT(int64_t, result, -32768, 32767)
            break;
        case 90:
            // limit as defined in dptconvert
            FCB_LIMIT(double, result, -671088.64, 670433.28)
            break;
        case 120:
            FCB_LIMIT(int64_t, result, 0 ,4294967295)
            break;
        case 130:
            FCB_LIMIT(int64_t, result, -2147483648, 2147483647)
            break;
        case 140:
            // limit as defined in dptconvert
            FCB_LIMIT(double, result, (-8388608.0 * pow(2, 255)), (8388607.0 * pow(2, 255)))
            break;
        default:
            break;
    }
}
