#pragma once
#include "FunctionBlock.h"
#include "OpenKNX/DateTime.h"

#define FCB_TEXT_FORMAT_MAX_INPUTS 4

class TextFormatBlock : public FunctionBlock
{
    // <Enumeration Text="Ab 5 Aufrunden" Value="0" Id="%ENID%" />
    // <Enumeration Text="Immer aufrunden" Value="1" Id="%ENID%" />
    // <Enumeration Text="Immer abrunden" Value="2" Id="%ENID%" />
    enum class RoundType
    {
        Nearest = 0,
        Up = 1,
        Down = 2,
    };

    std::string _format;
    std::string _textBlockOn;
    std::string _textBlockOff;
    char _thousandSeparator;

    bool _hasContinousTime = false;
    uint32_t _lastTimeUpdate = 0;
    OpenKNX::DateTime _tPlaceholders[FCB_TEXT_FORMAT_MAX_INPUTS];
    void updatePlaceholder(const byte idx);

    std::string formatBit(int input, bool value, uint8_t koNr);
    std::string formatDecimal(int input, int64_t value, uint8_t koNr);
    std::string formatFloat(int input, double value, uint8_t koNr);
    std::string formatTime(int input);
    std::string doFormat(int input, double value, uint8_t koNr, int decimalPlaces, char rightPadChar);
    void updateTextKo(bool forceSend);
    double roundToSignificant(double value, int digits, RoundType type, bool roundZeroFive);
    double roundToDecimalPlaces(double value, int decimalPlaces, RoundType type, bool roundZeroFive);
    double roundValue(TextFormatBlock::RoundType type, double factor, double scaledValue, bool roundZeroFive);
    std::string formatNumberString(const std::string &numberString, char thousandSep, char decimalSep, int minIntegerDigits, char padChar, bool fillupRight);

  public:
    TextFormatBlock(uint8_t channelIndex);

    void loop() override;

    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;
};