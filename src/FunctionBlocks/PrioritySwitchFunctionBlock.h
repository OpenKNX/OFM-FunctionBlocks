#pragma once
#include "FunctionBlock.h"

class PrioritySwitchFunctionBlock : public FunctionBlock
{
    uint8_t getParamInput(uint8_t input);
    uint8_t getParamInputBehavior(uint8_t input);
    uint8_t getParamOutByte(uint8_t input);
    uint8_t getParamOutPercent(uint8_t input);
    void setOutputForPrio(uint8_t input);
  public:
    PrioritySwitchFunctionBlock(uint8_t channelIndex);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;
};