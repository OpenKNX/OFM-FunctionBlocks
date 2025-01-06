#pragma once
#include "FunctionBlock.h"

class SelectionBlock : public FunctionBlock
{
  private:
    uint8_t _currentIndex = 255;
    void setNewIndex(uint8_t newIndex);
    void copyToOutput(GroupObject &ko);
  public:
    SelectionBlock(uint8_t channelIndex);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;  
};