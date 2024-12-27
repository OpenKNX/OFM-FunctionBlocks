#pragma once
#include "FunctionBlock.h"

enum class LogicFunctionBlockType
{
    LogicAND,
    LogicOR,
    LogicCOUNT,
};

class LogicFunctionBlock : public FunctionBlock
{
    const LogicFunctionBlockType _type;
    uint8_t getParamInput(uint8_t input);
    uint8_t getParamInputBehavior(uint8_t input);
  public:
    LogicFunctionBlock(uint8_t channelIndex, LogicFunctionBlockType type);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;
};