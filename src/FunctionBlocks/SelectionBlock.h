#pragma once
#include "FunctionBlock.h"

class SelectionBlock : public FunctionBlock
{
  private:
   
  public:
    SelectionBlock(uint8_t channelIndex);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;  
};