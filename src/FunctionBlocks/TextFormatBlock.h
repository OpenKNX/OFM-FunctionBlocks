#pragma once
#include "FunctionBlock.h"

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
    std::string formatBit(bool value, uint8_t koNr);
    std::string formatDecimal(int64_t value, uint8_t koNr);
    std::string formatFloat(double value, uint8_t koNr);
    void updateTextKo(bool forceSend);
    double roundToSignificant(double value, int digits, RoundType type, bool roundZeroFive);
    double roundToDecimalPlaces(double value, int decimalPlaces, RoundType type, bool roundZeroFive);
    double roundValue(TextFormatBlock::RoundType type, double factor, double scaledValue, bool roundZeroFive);
    std::string formatNumberString(const std::string &input, char thousandSep, char decimalSep, int minIntegerDigits, char padChar, bool fillupRight);

  public:
    TextFormatBlock(uint8_t channelIndex);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;
    bool processCommand(const std::string cmd, bool diagnoseKo) override;
};