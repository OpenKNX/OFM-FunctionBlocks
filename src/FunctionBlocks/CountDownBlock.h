#pragma once
#include "FunctionBlock.h"

class CountDownBlock : public FunctionBlock
{
  private:
    uint64_t _remainingSeconds = 0ul;
    unsigned long _lastValueUpdate = 0;
    unsigned long _waitForTriggerEnd = 0;
    int32_t _triggerEnd = 0;
    uint64_t _targetSeconds = 0;
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
    void finished();
    void updateRemainingKo();
    void updateTextKo(bool forceSend, bool end = false);
#ifdef OPENKNX_FCB_DEBUG
    bool processCommand(const std::string cmd, bool diagnoseKo) override;
#endif

};