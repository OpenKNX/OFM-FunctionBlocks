#include "../FunctionBlocksModule.h"
#include "TextFormatBlock.h"
#include <algorithm>

#define KoFCB_CHText KoFCB_CHKO9

TextFormatBlock::TextFormatBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "TextFormat")
{   
    _format =  ParamFCB_CHFormatStringStr;
    logDebugP("TextFormatBlock2 format string: '%s'", _format.c_str());
    _thousandSeparator = ((const char*)ParamFCB_CHFormatThousand)[0];
    _textBlockOn = ParamFCB_CHFormatOnStr;
    _textBlockOff = ParamFCB_CHFormatOffStr;
}
#define FCB_TEXT_FORMAT_MAX_INPUTS 4

/*************************** IMPORTANT **************************/
/*                                                              */
/*  DO NOT use none input related parameters after these lines  */
/*                                                              */
/*************************** IMPORTANT **************************/

#undef FCB_ParamCalcIndex
#define FCB_ParamCalcIndex(index) (index + FCB_ParamBlockOffset + _channelIndex * FCB_ParamBlockSize + (input - 1) * (FCB_CHFormatIn2 - FCB_CHFormatIn1))

void TextFormatBlock::readInputKos()
{
    for (int input = 1; input <= FCB_TEXT_FORMAT_MAX_INPUTS; input++)
    {
        if (ParamFCB_CHFormatIn1 != 0)
        {
            auto& ko = getKo(0);
            if (!ko.initialized())
                ko.requestObjectRead();
        }
    }
}

void TextFormatBlock::initMissingInputValues()
{
    updateTextKo(true);
}

void TextFormatBlock::handleKo(GroupObject& ko)
{
    updateTextKo(false);
}

std::string TextFormatBlock::formatBit(int input, bool value, uint8_t koNr)
{
    // <Enumeration Text="Textbausteine aus 'Format Optionen'" Value="1" Id="%ENID%" />
    // <Enumeration Text="0 / 1" Value="2" Id="%ENID%" />
    // <Enumeration Text="Aus / Ein" Value="0" Id="%ENID%" />
    // <Enumeration Text="Inaktiv / Aktiv" Value="3" Id="%ENID%" />
    // <Enumeration Text="OK / Fehler" Value="4" Id="%ENID%" />
    // <Enumeration Text="Normal / Störung" Value="5" Id="%ENID%" />
    // <Enumeration Text="Bereit / Alarm" Value="6" Id="%ENID%" />
    // <Enumeration Text="Geschlossen / Offen" Value="7" Id="%ENID%" />
    // <Enumeration Text="Zu / Auf" Value="8" Id="%ENID%" />
    // <Enumeration Text="Versperrt / Entsperrt" Value="9" Id="%ENID%" />
    // <Enumeration Text="Verriegelt / Entriegelt" Value="10" Id="%ENID%" />
    // <Enumeration Text="Abwesend / Anwesend" Value="11" Id="%ENID%" />
    switch (ParamFCB_CHFormatBit1)
    {
        case 1:
            return value ? _textBlockOn : _textBlockOff;
        case 2:
            return std::string(value ? "1" : "0");
        case 3:
            return std::string(value ? "Aktiv" : "Inaktiv");
        case 4:
            return std::string(value ? "Fehler" : "OK");
        case 5:
            return std::string(value ? "Störung" : "Normal");
        case 6:
            return std::string(value ? "Alarm" : "Bereit");
        case 7:
            return std::string(value ? "Offen" : "Geschlossen");
        case 8:
            return std::string(value ? "Auf" : "Zu");
        case 9:
            return std::string(value ? "Entsperrt" : "Versperrt");
        case 10:
            return std::string(value ? "Entriegelt" : "Verriegelt");
        case 11:
            return std::string(value ? "Anwesend" : "Abwesend");
        case 0:
            return std::string(value ? "Ein" : "Aus");
        default:
            logErrorP("Unknown format type for bit: %d", ParamFCB_CHFormatBit1);
            return std::string(value ? "1" : "0");
    }
}

double TextFormatBlock::roundToSignificant(
    double value,
    int digits,
    RoundType type,
    bool roundZeroFive)
{
    if (value == 0.0)
        return 0.0;

    double sign = (value < 0.0) ? -1.0 : 1.0;
    value = std::abs(value);

    // Scale
    double d = std::ceil(std::log10(value));
    double factor = std::pow(10.0, digits - d);
    double scaledValue = value * factor;
    return roundValue(type, factor, scaledValue, roundZeroFive) * sign;
}

double TextFormatBlock::roundToDecimalPlaces(
    double value,
    int decimalPlaces,
    RoundType type,
    bool roundZeroFive)
{
    if (roundZeroFive)
        decimalPlaces--;

    double factor = std::pow(10.0, decimalPlaces);
    double scaledValue = value * factor;
  
    return roundValue(type, factor, scaledValue, roundZeroFive);
}

double TextFormatBlock::roundValue(TextFormatBlock::RoundType type, double factor, double scaledValue, bool roundZeroFive)
{
    if (roundZeroFive)
        scaledValue *= 2.0;
    double result = scaledValue;
    // Normal rounding
    switch (type)
    {
        case RoundType::Up:
            result = std::ceil(scaledValue);
            break;

        case RoundType::Down:
            result = std::floor(scaledValue);
            break;

        case RoundType::Nearest:
        default:
            result = std::round(scaledValue);
            break;
    }
    if (roundZeroFive)
        result /= 2.0;

    return result / factor;
}

std::string TextFormatBlock::formatDecimal(int input, int64_t value, uint8_t koNr)
{
    return doFormat(input, static_cast<double>(value), koNr, -1, '\0');
}

std::string TextFormatBlock::formatFloat(int input, double value, uint8_t koNr)
{
    char rightPadChar = '\0';
    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="Mit 0" Value="1" Id="%ENID%" />
    // <Enumeration Text="Mit Leerzeichen" Value="2" Id="%ENID%" />
    switch (ParamFCB_CHFormatFillupAfterComma1)
    {
        case 1:
            rightPadChar = '0';
            break;
        case 2:
            rightPadChar = ' ';
            break;
    }
    return doFormat(input, value, koNr, ParamFCB_CHFormatDecimalPlaces1, rightPadChar);
}

std::string TextFormatBlock::doFormat(int input, double value, uint8_t koNr, int decimalPlaces, char rightPadChar)
{
    std::string result;
    logDebugP("Formatting float value: %f", value);
    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="Nachkommastellen" Value="1" Id="%ENID%" />
    // <Enumeration Text="Genauigkeit (Stellenanzahl)" Value="2" Id="%ENID%" />
    char buffer[64];
    switch (ParamFCB_CHFormatRoundFloat1)
    {
        case 1: {
            RoundType type = static_cast<RoundType>(ParamFCB_CHFCBFormatRoundType1);
            bool roundZeroFive = ParamFCB_CHFCBFormatRound5_1;
            double roundedValue = roundToDecimalPlaces(value, decimalPlaces, type, roundZeroFive);
            logDebugP("Rounded value: %lf", roundedValue);
            snprintf(buffer, sizeof(buffer), "%.14g", roundedValue);
            result = buffer;
            logDebugP("Result value: %s", result.c_str());
            break;
        }
        case 2: {
            int significantDigits = ParamFCB_CHFormatSignificant1;
            RoundType type = static_cast<RoundType>(ParamFCB_CHFCBFormatRoundType1);
            bool roundZeroFive = ParamFCB_CHFCBFormatRound5_1;
            double roundedValue = roundToSignificant(value, significantDigits, type, roundZeroFive);
            logDebugP("Rounded significant value: %lf", roundedValue);
            snprintf(buffer, sizeof(buffer), "%.14g", roundedValue);
            result = buffer;
            logDebugP("Result value: %s", result.c_str());
            break;
        }
        case 0:
        default:
            snprintf(buffer, sizeof(buffer), "%.14g", value);
            result = buffer;
            logDebugP("Result value: %s", result.c_str());
            break;
    }
    // <Enumeration Text="Deaktiviert" Value="0" Id="%ENID%" />
    // <Enumeration Text="Links mit 0" Value="1" Id="%ENID%" />
    // <Enumeration Text="Links mit Leerzeichen" Value="2" Id="%ENID%" />
    // <Enumeration Text="Rechts mit Leerzeichen" Value="3" Id="%ENID%" />
    char padChar = '\0';
    bool fillupRight = false;
    int minIntegerDigits = ParamFCB_CHFormatFillupPrecomma1;
    switch (ParamFCB_CHFormatFillupMode1)
    {
        case 0:
            minIntegerDigits = -1;
            break;
        case 1:
            padChar = '0';
            break;
        case 2:
            padChar = ' ';
            break;
        case 3:
            padChar = ' ';
            fillupRight = true;
            break;
    }
    if (rightPadChar != '\0' && decimalPlaces > 0)
    {
        // Add right padding after decimal point
        std::size_t pos = result.rfind('.');
        if (pos == std::string::npos)
        {
           result += '.' + std::string(decimalPlaces, rightPadChar);
        }
        else
        {
            std::size_t currentDecimals = result.length() - pos - 1;
            if (static_cast<int>(currentDecimals) < decimalPlaces)
            {
                result += std::string(decimalPlaces - currentDecimals, rightPadChar);
            }
        }
    }
    result = formatNumberString(result, _thousandSeparator, ',', ParamFCB_CHFormatFillupLength1, padChar, fillupRight);
    return result;
}

std::string TextFormatBlock::formatNumberString(
    const std::string& numberString,
    char thousandSep,
    char decimalSep,
    int minIntegerDigits, // minimum number of integer digits (no sign, no separators)
    char padChar,         // '0' or ' '
    bool fillupRight)
{
    logDebugP("Formatting number string: '%s' min: %d  padChar: '%c' right: %d", numberString.c_str(), minIntegerDigits, padChar, fillupRight);
    //  Extract optional sign
    char sign = '\0';
    size_t start = 0;
    if (!numberString.empty() && (numberString[0] == '-' || numberString[0] == '+'))
    {
        sign = numberString[0];
        start = 1;
    }

    // Split integer and fractional parts
    size_t dotPos = numberString.find('.', start);

    std::string integerPart =
        (dotPos == std::string::npos)
            ? numberString.substr(start)
            : numberString.substr(start, dotPos - start);

    std::string fractionalPart =
        (dotPos == std::string::npos)
            ? ""
            : numberString.substr(dotPos + 1);

    // Pad integer digits (before thousand separators)
    if (padChar == '0' && minIntegerDigits > 0 &&
        static_cast<int>(integerPart.size()) < minIntegerDigits && !fillupRight)
    {

        int padCount = minIntegerDigits - static_cast<int>(integerPart.size());
        integerPart.insert(0, padCount, padChar);
    }

    // Insert thousand separators
    std::string formattedInt;
    int count = 0;
    for (auto it = integerPart.rbegin(); it != integerPart.rend(); ++it)
    {
        if (count == 3)
        {
            if (thousandSep != '\0')
                formattedInt += thousandSep;
            count = 0;
        }
        formattedInt += *it;
        ++count;
    }
    std::reverse(formattedInt.begin(), formattedInt.end());

    // Combine sign and integer part
    std::string result;
    if (sign != '\0')
    {
        result += sign;
    }
    result += formattedInt;

    // Append fractional part
    if (!fractionalPart.empty())
    {
        result += decimalSep;
        result += fractionalPart;
    }

    // Final padding with spaces if needed
    if (padChar == ' ' && minIntegerDigits > 0)
    {
        if (fillupRight)
        {
            // Apply space padding to the RIGHT of the whole number
            int digitCount = 0;
            for (char c : result)
            {
                if (c != sign && c != thousandSep)
                    digitCount++;
            }
            int spaceCount = minIntegerDigits - digitCount;
            if (spaceCount > 0)
                result += std::string(spaceCount, ' ');
        }
        else
        {
             // Apply space padding to the LEFT of the whole number
            int digitCount = static_cast<int>(integerPart.size());
            int spaceCount = minIntegerDigits - digitCount;
            if (spaceCount > 0)
            {
                result.insert(0, spaceCount, ' ');
            }
        }
    }
    return result;
}

void TextFormatBlock::updateTextKo(bool forceSend)
{
    std::string result;
    bool waitForParameter = false;
    for (size_t i = 0; i < _format.length() && result.length() < 14; i++)
    {
        auto c = _format[i];
        if (waitForParameter)
        {
            waitForParameter = false;
            if (c >= '1' && c <= '0' + FCB_TEXT_FORMAT_MAX_INPUTS)
            {
                uint8_t koNr = c - '1';
                int input = c - '0';
                auto inTypeId = ParamFCB_CHFormatIn1;
                switch (inTypeId)
                {
                    case 10: // Bit
                        result += formatBit(input, (bool)getKo(koNr).value(DPT_Switch), koNr);
                        break;
                    case 50:
                        result += formatDecimal(input, (int64_t)getKo(koNr).value(DPT_Value_1_Ucount), koNr);
                        break;
                    case 51:
                        result += formatDecimal(input, (int64_t)getKo(koNr).value(DPT_Scaling), koNr);
                        break;
                    case 61:
                        result += formatDecimal(input, (int64_t)getKo(koNr).value(DPT_Value_1_Count), koNr);
                        break;
                    case 70:
                        result += formatDecimal(input, (int64_t)getKo(koNr).value(DPT_Value_2_Ucount), koNr);
                        break;
                    case 80:
                        result += formatDecimal(input, (int64_t)getKo(koNr).value(DPT_Value_2_Count), koNr);
                        break;
                    case 90:
                        result += formatFloat(input, (double)getKo(koNr).value(DPT_Value_Temp), koNr);
                        break;
                    case 120:
                        result += formatDecimal(input, (int64_t)getKo(koNr).value(DPT_Value_4_Ucount), koNr);
                        break;
                    case 130:
                        result += formatDecimal(input, (int64_t)getKo(koNr).value(DPT_Value_4_Count), koNr);
                        break;
                    case 140:
                        result += formatFloat(input, (double)getKo(koNr).value(DPT_Value_Amplitude), koNr);
                        break;
                    case 160:
                        result += (const char*)getKo(koNr).value(DPT_String_8859_1);
                        break;
                }
                continue;
            }
        }
        else if (c == '@')
        {
            waitForParameter = true;
            continue;
        }
        result += _format[i];
    }
    if (result.length() > 14)
        result = result.substr(0, 14);

    logDebugP("Formatted text: '%s'", result.c_str());
    KoFCB_CHText.valueCompare(result.c_str(), DPT_String_8859_1);
    if (forceSend)
        KoFCB_CHText.objectWritten();
}
