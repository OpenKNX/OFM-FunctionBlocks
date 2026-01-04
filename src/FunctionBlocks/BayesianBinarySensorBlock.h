#pragma once
#include "FunctionBlock.h"

class BayesianBinarySensorBlock : public FunctionBlock
{
  private:
    uint8_t getParamInputEnabled(uint8_t input);
    uint8_t getParamProbGivenTrue(uint8_t input);
    uint8_t getParamProbGivenFalse(uint8_t input);

    uint8_t _calculateBayesianProbability();
    void _updateOutputs(uint8_t probabilityPercent);
    
  public:
    BayesianBinarySensorBlock(uint8_t channelIndex);
    
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;
};