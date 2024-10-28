#pragma once
#include "FunctionBlock.h"

enum class SimpleAggregationBlockType
{
    AggrSUM,
    AggrAVG,
    AggrMIN,
    AggrMAX,
    AggrWidth,
    /*
    AggrMedian,
    AggrQ25,
    AggrQ75,
    AggrSTD,
    */
};

class SimpleAggregationBlock : public FunctionBlock
{
  private:
    const SimpleAggregationBlockType _type;
    uint8_t getParamInput(uint8_t input);
    /*
    uint8_t getParamInputBehavior(uint8_t input);
    */
  public:
    SimpleAggregationBlock(uint8_t channelIndex, SimpleAggregationBlockType type);

    // TODO remove here
    void readInputKos() override;
    // TODO remove here
    void initMissingInputValues() override;

    void handleKo(GroupObject &ko) override;
};