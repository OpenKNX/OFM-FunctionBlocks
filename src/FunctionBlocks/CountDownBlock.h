#pragma once
#include "FunctionBlock.h"

class CountDownBlock : public FunctionBlock
{
  private:
    uint64_t _remainingSeconds = 0ul;
    unsigned long _lastValueUpdate = 0;
    bool _pause = false;
  public:
    CountDownBlock(uint8_t channelIndex);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;  
    void start(uint64_t startValue);
    void pause(bool pause);
    void stop();
    void loop() override;
    void updateRemainingKo();
    void updateTextKo(bool forceSend, bool end = false);

};