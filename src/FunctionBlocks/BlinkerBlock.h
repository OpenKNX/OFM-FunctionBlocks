#pragma once
#include "FunctionBlock.h"

class BlinkerBlock : public FunctionBlock
{
  private:
    unsigned long _phaseStart = 0;
    bool _isOn = false;
    uint8_t _blinkCounter = 0;
    uint8_t _startValue = 0;
    bool _hasActorFeedbackKO = false;
    void start();
    void breakRequest();
    void stop();
    void setOutput(bool value);
  public:
    BlinkerBlock(uint8_t channelIndex);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;  
    void loop() override;
   
};