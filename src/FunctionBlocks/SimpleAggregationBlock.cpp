#include "SimpleAggregationBlock.h"
#include "knxprod.h"

#define TYPE2Str(type)                                                                                            \
    type == SimpleAggregationBlockType::AggrSUM ? "SUM" : type == SimpleAggregationBlockType::AggrAVG  ? "AVG"    \
                                                      : type == SimpleAggregationBlockType::AggrMIN    ? "MIN"    \
                                                      : type == SimpleAggregationBlockType::AggrMAX    ? "MAX"    \
                                                      : "Range"
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

int8_t SimpleAggregationBlock::getParamInputWeight(uint8_t input)
{
    if (ParamFCB_CHAggWeight == 0)
    {
        // no individual weight
        return 1;
    }
    switch (input)
    {
        case 0:
            return ParamFCB_CHAggKo0W;
        case 1:
            return ParamFCB_CHAggKo1W;
        case 2:
            return ParamFCB_CHAggKo2W;
        case 3:
            return ParamFCB_CHAggKo3W;
        case 4:
            return ParamFCB_CHAggKo4W;
        case 5:
            return ParamFCB_CHAggKo5W;
        case 6:
            return ParamFCB_CHAggKo6W;
        case 7:
            return ParamFCB_CHAggKo7W;
        case 8:
            return ParamFCB_CHAggKo8W;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid input");
            return 0;
    }
}

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
        _update();
    }
}

void SimpleAggregationBlock::_update()
{
    const Dpt dptInput = dptType(ParamFCB_CHAggInputDpt);

    // Recalc the output
    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();
    double sum = 0.0;
    int16_t absWeightSum = 0.0;
    uint8_t count = 0;
    for (uint8_t i = 0; i < 9; i++)
    {
        // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Aktiv" Value="1" Id="%ENID%" />
        if (getParamInput(i) == 0)
        {
            continue;
        }

        if (!hasValue(i))
        {
            // TODO handling of incomplete input values; current implementation requires all
            logDebugP("  input(%d) NOT has value", i);
            return;
        }

        const int8_t inputWeight = getParamInputWeight(i);
        const double inputValue = getKo(i).value(dptInput);
        min = MIN(min, inputValue);
        max = MAX(max, inputValue);
        sum += inputValue * inputWeight;
        absWeightSum += abs(inputWeight);
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
            result = sum / absWeightSum;
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
        default:
            break;
    }
    _updateOutput(result);
}

void SimpleAggregationBlock::_updateOutput(KNXValue& result)
{
    logDebugP("  result %f (of type %d)", result, _type);

    const Dpt dptOutput = dptType(ParamFCB_CHAggOutputDptEff);

    // rounding for integer outputs
    if ((dptOutput.mainGroup != 9) && (dptOutput.mainGroup != 14))
    {
        if (ParamFCB_CHAggOutputRounding)
        {
            result = (int64_t)round((double)result);
        }
        else
        {
            // integer output
            result = (int64_t)result;
        }
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
