#include "ValueMonitorBlock.h"

#define FCB_KoCHSInput FCB_KoCHKO0
#define KoFCB_CHSInput KoFCB_CHKO0

#define FCB_KoCHLastReceivedValueTimeStamp FCB_KoCHKO4
#define KoFCB_CHLastReceivedValueTimeStamp KoFCB_CHKO4

#define FCB_KoCHValueReceiveTimeout FCB_KoCHKO5
#define KoFCB_CHValueReceiveTimeout KoFCB_CHKO5

#define FCB_KoCHValueToLow FCB_KoCHKO6
#define KoFCB_CHValueToLow KoFCB_CHKO6

#define FCB_KoCHValueToHigh FCB_KoCHKO7
#define KoFCB_CHValueToHigh KoFCB_CHKO7

#define FCB_KoCHSummaryAlarm FCB_KoCHKO8
#define KoFCB_CHSummaryAlarm KoFCB_CHKO8

#define FCB_KoCHOutput FCB_KoCHKO9
#define KoFCB_CHSOutput KoFCB_CHKO9

std::vector<ValueMonitorBlock*> ValueMonitorBlock::_instances = std::vector<ValueMonitorBlock*>();

ValueMonitorBlock::ValueMonitorBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "ValueMonitor"),
      _lastValidValue(false)
{
    setAlarmState(ValueMonitorAlarmState::NoAlarm, "Initializing ValueMonitorBlock");
    _dpt = dptType(ParamFCB_CHMonitoringValueType);
    _watchDogFallbackBehaviour = (ValueMonitorWatchdogFallbackBehavior)ParamFCB_CHMonitoringWDBehavior;

    // <Enumeration Text="Aus" Value="0" Id="%ENID%" />
    // <Enumeration Text="10 WDuten" Value="1" Id="%ENID%" />
    // <Enumeration Text="30 WDuten" Value="2" Id="%ENID%" />
    // <Enumeration Text="1 Stunde" Value="3" Id="%ENID%" />
    // <Enumeration Text="2 Stunden" Value="4" Id="%ENID%" />
    // <Enumeration Text="3 Stunden" Value="5" Id="%ENID%" />
    // <Enumeration Text="4 Stunden" Value="6" Id="%ENID%" />
    // <Enumeration Text="8 Stunden" Value="7" Id="%ENID%" />
    // <Enumeration Text="12 Stunden" Value="8" Id="%ENID%" />
    if (ParamFCB_CHMonitoringWDEnabled)
        _waitForValueTimeoutMs = ParamFCB_CHMonitoringWDTTimeoutDelayTimeMS;
    setState(ValueMonitorWatchdogState::Disabled);
    

    if (!KoFCB_CHValueToLow.initialized())
        KoFCB_CHValueToLow.value(false, DPT_Switch);
    if (!KoFCB_CHValueToHigh.initialized())
        KoFCB_CHValueToHigh.value(false, DPT_Switch);
    if (!KoFCB_CHSummaryAlarm.initialized())
        KoFCB_CHSummaryAlarm.value(false, DPT_Switch);
    _instances.push_back(this);
}

const std::vector<ValueMonitorBlock*>& ValueMonitorBlock::getInstances()
{
    return _instances;
}

void ValueMonitorBlock::readInputKos()
{
    if (!KoFCB_CHSInput.initialized())
    {
        if (_waitForValueTimeoutMs > 0)
        {
            _waitTimeStartMillis = max(1UL, millis());
            // Watchdog is enabled
            switch (_watchDogFallbackBehaviour)
            {
                case ValueMonitorWatchdogFallbackBehavior::RequestValueAndIgnore:
                case ValueMonitorWatchdogFallbackBehavior::RequestValueAndProvideFallbackValue:
                    // <Enumeration Text="Nichts" Value="1" Id="%ENID%" />
                    // <Enumeration Text="Leseanforderung, dann Alarm wenn Zeitüberwachung konfiguriert" Value="0" Id="%ENID%" />	         
                    if (ParamFCB_CHMonitoringStart == 0) // Leseanforderung, dann Alarm
                    {
                        setState(ValueMonitorWatchdogState::WaitForResponseValue);
                        KoFCB_CHSInput.requestObjectRead();
                        setAlarmState(ValueMonitorAlarmState::NoAlarm, "Requesting initial value read");
                    }
                    else
                    {
                        setState(ValueMonitorWatchdogState::WaitForTimeout);
                    }
                    break;
                default:
                    setState(ValueMonitorWatchdogState::WaitForTimeout);
                    break;
            }
        }
        else
        {
            // <Enumeration Text="Nichts" Value="1" Id="%ENID%" />
            // <Enumeration Text="Leseanforderung, dann Alarm wenn Zeitüberwachung konfiguriert" Value="0" Id="%ENID%" />	         
            if (ParamFCB_CHMonitoringStart == 0) // Leseanforderung, dann Alarm
            {
                KoFCB_CHSInput.requestObjectRead();
            }
        }  
    }
}

void ValueMonitorBlock::initMissingInputValues()
{
}

void ValueMonitorBlock::handleKo(GroupObject &ko)
{
    if (FCB_KoCalcIndex(ko.asap()) == FCB_KoCHSInput)
    {
        switch (ParamFCB_CHMonitoringValueType)
        {
            case 10:
                handleInputKo<bool>(ko, ParamFCB_CHMonitoringMinDpt1, ParamFCB_CHMonitoringMaxDpt1);
                break;
            case 50:
                handleInputKo<int64_t>(ko, ParamFCB_CHMonitoringMinDpt5, ParamFCB_CHMonitoringMaxDpt5);
                break;
            case 51:
                handleInputKo<int64_t>(ko, ParamFCB_CHMonitoringMinDpt5001, ParamFCB_CHMonitoringMaxDpt5001);
                break;
            case 61:
                handleInputKo<int64_t>(ko, ParamFCB_CHMonitoringMinDpt6, ParamFCB_CHMonitoringMaxDpt6);
                break;
            case 70:
                handleInputKo<int64_t>(ko, ParamFCB_CHMonitoringMinDpt7, ParamFCB_CHMonitoringMaxDpt7);
                break;
            case 80:
                handleInputKo<int64_t>(ko, ParamFCB_CHMonitoringMinDpt8, ParamFCB_CHMonitoringMaxDpt8);
                break;
            case 90:
                handleInputKo<double>(ko, ParamFCB_CHMonitoringMinDpt9, ParamFCB_CHMonitoringMaxDpt9);
                break;
            case 120:
                handleInputKo<int64_t>(ko, ParamFCB_CHMonitoringMinDpt12, ParamFCB_CHMonitoringMaxDpt12);
                break;
            case 130:
                handleInputKo<int64_t>(ko, ParamFCB_CHMonitoringMinDpt13, ParamFCB_CHMonitoringMaxDpt13);
                break;
            case 140:
                handleInputKo<double>(ko, ParamFCB_CHMonitoringMinDpt14, ParamFCB_CHMonitoringMaxDpt14);
                break;
            case 160:
                setAlarmState(ValueMonitorAlarmState::NoAlarm, "No Alarm");
                resetWatchdog();
                if (_waitForValueTimeoutMs != 0)
                    KoFCB_CHSummaryAlarm.valueCompare(false, DPT_Alarm);
                handleLastValidTelegram(ko, true);
                break;
            default:
                break;
        }
    }
}

void ValueMonitorBlock::setAlarmState(ValueMonitorAlarmState state, const char* logMessage)
{
    //logDebugP("ValueMonitorBlock: %s", logMessage);
    _alarmState = state;
}

ValueMonitorAlarmState ValueMonitorBlock::alarmState() const
{
    return _alarmState;
}

void ValueMonitorBlock::resetWatchdog()
{
    if (_waitForValueTimeoutMs != 0)
    {
        if (_watchDogState != ValueMonitorWatchdogState::Disabled)
        {
            _waitTimeStartMillis = max(1UL, millis());
            setState(ValueMonitorWatchdogState::WaitForTimeout);
        }
        KoFCB_CHValueReceiveTimeout.valueCompare(false, DPT_Switch);
    }
}

void ValueMonitorBlock::handleLastValidTelegram(GroupObject &ko, bool isValid)
{
    if (isValid)
    {
        if (openknx.time.isValid())
        {
            tm tm = openknx.time.getLocalTime().toTm();
            tm.tm_year += 1900;
            tm.tm_mon += 1;
            KoFCB_CHLastReceivedValueTimeStamp.valueCompare(tm, DPT_DateTime);
        }
        else
        {
            _lastValidTelegramWhileNotTimeAvailable = max(1UL, millis());
        }
        _lastValidValue = ko.value(_dpt);
        _hasValidValue = true;
        sendValue(_lastValidValue, true);
    }
}

template <typename T>
void ValueMonitorBlock::handleInputKo(GroupObject &ko, T minValue, T maxValue)
{
    resetWatchdog();
    bool toLow = false;
    bool hasSummaryAlarm = false;
    if (ParamFCB_CHMonitoringMin > 0)
    {
        hasSummaryAlarm = true;
        toLow = ((T)ko.value(_dpt)) < minValue;
        KoFCB_CHValueToLow.valueCompare(toLow, DPT_Switch);
    }
    bool toHigh = false;
    if (ParamFCB_CHMonitoringMax > 0)
    {
        hasSummaryAlarm = true;
        toHigh = ((T)ko.value(_dpt)) > maxValue;
        KoFCB_CHValueToHigh.valueCompare(toHigh, DPT_Switch);
    }
    bool isValid = !toLow && !toHigh;
    handleLastValidTelegram(ko, isValid);
    if (!hasSummaryAlarm)
    {
       hasSummaryAlarm = _waitForValueTimeoutMs != 0;
    }
    if (hasSummaryAlarm)
    {
        KoFCB_CHSummaryAlarm.valueCompare(!isValid, DPT_Alarm);
    }
    
    if (toLow)
    {
        setAlarmState(ValueMonitorAlarmState::ValueTooLow, "Value too low");
        T replacementValue;
        //	<Enumeration Text="Überwachung deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Nichts senden" Value="1" Id="%ENID%" />
        // <Enumeration Text="Letzten gültigen Wert" Value="2" Id="%ENID%" />
        // <Enumeration Text="Grenzwert" Value="3" Id="%ENID%" />
        switch (ParamFCB_CHMonitoringMin)
        {
            case 2:
                if (!_hasValidValue)
                    return;
                replacementValue = _lastValidValue;
                break;
            case 3:
                replacementValue = minValue;
                break;
            default:
                return;
        }
        sendValue(replacementValue, false);
    }
    else if (toHigh)
    {
        setAlarmState(ValueMonitorAlarmState::ValueTooHigh, "Value too high");
        T replacementValue;
        //	<Enumeration Text="Überwachung deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Nichts senden" Value="1" Id="%ENID%" />
        // <Enumeration Text="Letzten gültigen Wert" Value="2" Id="%ENID%" />
        // <Enumeration Text="Grenzwert" Value="3" Id="%ENID%" />
        switch (ParamFCB_CHMonitoringMax)
        {
            case 2:
                if (!_hasValidValue)
                    return;
                replacementValue = _lastValidValue;
                break;
            case 3:
                replacementValue = maxValue;
                break;
            default:
                return;
        }
        sendValue(replacementValue, false);
    }
    else
    {
        setAlarmState(ValueMonitorAlarmState::NoAlarm, "Valid value received");
    }
}

template <typename T>
void ValueMonitorBlock::sendValue(T value, bool isValid)
{
    // <Enumeration Text="Ersatzwerte auf Eingang senden" Value="0" Id="%ENID%" />
    // <Enumeration Text="Getrenntes Ausgangsobjekt, nur gültige Werte" Value="1" Id="%ENID%" />
    // <Enumeration Text="Getrenntes Ausgangsobjekt, gültige und Ersatzwerte" Value="2" Id="%ENID%" />
    // <Enumeration Text="Getrenntes Ausgangsobjekt, nur Ersatzwerte" Value="3" Id="%ENID%" />
    switch (ParamFCB_CHMonitoringOutput)
    {
        case 0:
            if (!isValid)
                KoFCB_CHSInput.value(value, _dpt);
            break;
        case 1:
            if (isValid)
                KoFCB_CHSOutput.value(value, _dpt);
            break;
        case 2:
            KoFCB_CHSOutput.value(value, _dpt);
            break;
        case 3:
            if (!isValid)
                KoFCB_CHSOutput.value(value, _dpt);
            break;
    }
}

void ValueMonitorBlock::loop()
{
    if (_watchDogState != ValueMonitorWatchdogState::Disabled)
    {
        handleTimeout();
    }
    if (_lastValidTelegramWhileNotTimeAvailable > 0 && openknx.time.isValid())
    {
        auto localTime = openknx.time.getLocalTime();
        localTime.addSeconds((millis() - _lastValidTelegramWhileNotTimeAvailable) / -1000);
        tm tm = localTime.toTm();
        tm.tm_year += 1900;
        tm.tm_mon += 1;
        KoFCB_CHLastReceivedValueTimeStamp.valueCompare(tm, DPT_DateTime);
        _lastValidTelegramWhileNotTimeAvailable = 0;
    }
}

//   ValueMonitorWatchdogBehaviorOnlyAlarm = 0,
//     ValueMonitorWatchdogBehaviorRequestValueAndIgnore = 1,
//     ValueMonitorWatchdogBehaviorRequestValueAndProvideFallbackValue = 2,
//     ValueMonitorWatchdogBehaviorProvideFallbackValue = 3

void ValueMonitorBlock::handleTimeout()
{
    unsigned long currentMillis = max(1UL, millis());
    bool sendFallbackValue = false;
    bool setAlarm = false;
    switch (_watchDogState)
    {
        case ValueMonitorWatchdogState::WaitForTimeout:
            if (_waitForValueTimeoutMs > 0 && currentMillis - _waitTimeStartMillis > _waitForValueTimeoutMs)
            {
                switch (_watchDogFallbackBehaviour)
                {
                    case ValueMonitorWatchdogFallbackBehavior::RequestValueAndIgnore:
                    case ValueMonitorWatchdogFallbackBehavior::RequestValueAndProvideFallbackValue:
                        KoFCB_CHSInput.requestObjectRead();
                        setState(ValueMonitorWatchdogState::WaitForResponseValue);
                        setAlarmState(ValueMonitorAlarmState::WaitForValue, "Requesting value read");
                        break;
                    case ValueMonitorWatchdogFallbackBehavior::OnlyAlarm:
                        setAlarm = true;
                        setAlarmState(ValueMonitorAlarmState::Timeout, "Timeout alarm");
                        break;
                    case ValueMonitorWatchdogFallbackBehavior::ProvideFallbackValue:
                        sendFallbackValue = true;
                        setAlarm = true;
                        setAlarmState(ValueMonitorAlarmState::Timeout, "Timeout alarm");
                        break;
                }
                _waitTimeStartMillis = max(1UL, millis());
            }
            break;
        case ValueMonitorWatchdogState::WaitForResponseValue:
            if (_waitForValueTimeoutMs > 0 && currentMillis - _waitTimeStartMillis > _waitForValueAfterReadTimeoutMs)
            {
                switch (_watchDogFallbackBehaviour)
                {
                    case ValueMonitorWatchdogFallbackBehavior::RequestValueAndProvideFallbackValue:
                    case ValueMonitorWatchdogFallbackBehavior::ProvideFallbackValue:
                        sendFallbackValue = true;
                        break;
                }
                setAlarm = true;
                setAlarmState(ValueMonitorAlarmState::WaitForValue, "Timeout waiting for response value");
                _waitTimeStartMillis = max(1UL, millis());
                setState(ValueMonitorWatchdogState::WaitForTimeout);
            }
            break;
    }
    if (setAlarm)
    {
        KoFCB_CHSummaryAlarm.valueCompare(setAlarm, DPT_Alarm);
        KoFCB_CHValueReceiveTimeout.valueCompare(true, DPT_Switch);
    }
    if (sendFallbackValue)
    {
        switch (ParamFCB_CHMonitoringValueType)
        {
            case 10:
                sendValue<bool>(ParamFCB_CHMonitoringWDDpt1, false);
                break;
            case 50:
                sendValue<int64_t>(ParamFCB_CHMonitoringWDDpt5, false);
                break;
            case 51:
                sendValue<int64_t>(ParamFCB_CHMonitoringWDDpt5001, false);
                break;
            case 61:
                sendValue<int64_t>(ParamFCB_CHMonitoringWDDpt6, false);
                break;
            case 70:
                sendValue<int64_t>(ParamFCB_CHMonitoringWDDpt7, false);
                break;
            case 80:
                sendValue<int64_t>(ParamFCB_CHMonitoringWDDpt8, false);
                break;
            case 90:
                sendValue<double>(ParamFCB_CHMonitoringWDDpt9, false);
                break;
            case 120:
                sendValue<int64_t>(ParamFCB_CHMonitoringWDDpt12, false);
                break;
            case 130:
                sendValue<int64_t>(ParamFCB_CHMonitoringWDDpt12, false);
                break;
            case 140:
                sendValue<double>(ParamFCB_CHMonitoringWDDpt14, false);
                break;
            case 160:
                sendValue<const char*>((const char*)ParamFCB_CHMonitoringWDDpt16, false);
                break;
            default:
                break;
        }
    }
}

void ValueMonitorBlock::setState(ValueMonitorWatchdogState state)
{
    _watchDogState = state;
}
