#pragma once
#include "FunctionBlock.h"


enum ValueMonitorWatchdogState : uint8_t
{
    ValueMonitorWatchdogStateDisabled,
    ValueMonitorWatchdogStateWaitForResponseValue,
    ValueMonitorWatchdogStateWaitForTimeout
};

// <Enumeration Text="Nur Alarm auslösen" Value="0" Id="%ENID%" />
// <Enumeration Text="Leseanforderung, dann Alarm" Value="1" Id="%ENID%" />	
// <Enumeration Text="Leseanforderung, dann Ersatzwert und Alarm" Value="2" Id="%ENID%" />
// <Enumeration Text="Ersatzwert und Alarm" Value="3" Id="%ENID%" />
enum ValueMonitorWatchdogFallbackBehavior : uint8_t
{
    ValueMonitorWatchdogBehaviorOnlyAlarm = 0,
    ValueMonitorWatchdogBehaviorRequestValueAndIgnore = 1,
    ValueMonitorWatchdogBehaviorRequestValueAndProvideFallbackValue = 2,
    ValueMonitorWatchdogBehaviorProvideFallbackValue = 3
};

class ValueMonitorBlock : public FunctionBlock
{
  private:
    const static unsigned long _waitForValueAfterReadTimeoutMs = 10000;
   
    std::string _name;
    ValueMonitorWatchdogState _watchDogState = ValueMonitorWatchdogState::ValueMonitorWatchdogStateDisabled;
    unsigned long _waitForValueTimeoutMs = 0;
    unsigned long _waitTimeStartMillis = 0;
    unsigned long _lastValidTelegramWhileNotTimeAvailable = 0;
    Dpt _dpt;
    KNXValue _lastValidValue;
    bool hasValidValue = false;

    ValueMonitorWatchdogFallbackBehavior _watchDogFallbackBehaviour = ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorOnlyAlarm;
    void setState(ValueMonitorWatchdogState state);
    void handleTimeout();
    void logState();

  public:
    ValueMonitorBlock(uint8_t channelIndex);
    void readInputKos() override;
    void initMissingInputValues() override;
    void handleKo(GroupObject &ko) override;  
    template<typename T>
    void handleInputKo(GroupObject &ko, T min, T max);  
    template<typename T>
    void sendValue(T value, bool isValid);
    void start(uint64_t startValue);
    void pause(bool pause);
    void stop();
    void loop() override;
    void finished();
    void updateRemainingKo();
    void updateTextKo(bool forceSend, bool end = false);
};