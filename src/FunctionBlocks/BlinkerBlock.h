#pragma once
#include "FunctionBlock.h"

class BlinkerBlock : public FunctionBlock
{
  private:
    unsigned long _lastChange = 0;
    bool _isOn = false;
    uint8_t _onOffChangeCount = 0;
    uint8_t _startValue = 0;
    bool _hasActorFeedbackKO = false;
    void start(uint8_t count = 0);
    void breakRequest();
    void stop();
    void setOutput(bool value);
    void setOutputToStartValue();
  public:
    BlinkerBlock(uint8_t channelIndex);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;  
    void loop() override;
   
};