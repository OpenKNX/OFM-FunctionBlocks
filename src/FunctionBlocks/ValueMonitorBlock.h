#pragma once
#include "FunctionBlock.h"
#include "vector"


enum class ValueMonitorWatchdogState : uint8_t
{
    Disabled,
    WaitForResponseValue,
    WaitForTimeout
};

// <Enumeration Text="Nur Alarm auslösen" Value="0" Id="%ENID%" />
// <Enumeration Text="Leseanforderung, dann Alarm" Value="1" Id="%ENID%" />	
// <Enumeration Text="Leseanforderung, dann Ersatzwert und Alarm" Value="2" Id="%ENID%" />
// <Enumeration Text="Ersatzwert und Alarm" Value="3" Id="%ENID%" />
enum class ValueMonitorWatchdogFallbackBehavior : uint8_t
{
    OnlyAlarm = 0,
    RequestValueAndIgnore = 1,
    RequestValueAndProvideFallbackValue = 2,
    ProvideFallbackValue = 3
};

enum class ValueMonitorAlarmState : uint8_t
{
    NoAlarm = 0,
    WaitForValue = 1,
    ValueTooLow = 2,
    ValueTooHigh = 3,
    Timeout = 4,
};

class ValueMonitorBlock : public FunctionBlock
{
  private:
    static std::vector<ValueMonitorBlock*> _instances;
    const static unsigned long _waitForValueAfterReadTimeoutMs = 10000;
   
    std::string _name;
    ValueMonitorWatchdogState _watchDogState = ValueMonitorWatchdogState::Disabled;
    unsigned long _waitForValueTimeoutMs = 0;
    unsigned long _waitTimeStartMillis = 0;
    unsigned long _lastValidTelegramWhileNotTimeAvailable = 0;
    Dpt _dpt;
    KNXValue _lastValidValue;
    bool _hasValidValue = false;
    ValueMonitorAlarmState _alarmState = ValueMonitorAlarmState::WaitForValue;
   
    ValueMonitorWatchdogFallbackBehavior _watchDogFallbackBehaviour = ValueMonitorWatchdogFallbackBehavior::OnlyAlarm;
    void setState(ValueMonitorWatchdogState state);
    void setAlarmState(ValueMonitorAlarmState state, const char* logMessage);
    void handleTimeout();
    void logState();
    void resetWatchdog();
    void handleLastValidTelegram(GroupObject &ko, bool isValid);

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
    static const std::vector<ValueMonitorBlock*>& getInstances();
    ValueMonitorAlarmState alarmState() const;
};