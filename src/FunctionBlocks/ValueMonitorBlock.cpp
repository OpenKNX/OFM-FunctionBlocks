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

ValueMonitorBlock::ValueMonitorBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "ValueMonitor"),
      _lastValidValue(false)
{
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
    switch (ParamFCB_CHMonitoringWDTimeout)
    {
        case 0:
            break;
        case 1:
            _waitForValueTimeoutMs = 10 * 60 * 1000;
            break;
        case 2:
            _waitForValueTimeoutMs = 30 * 60 * 1000;
            break;
        case 3:
            _waitForValueTimeoutMs = 60 * 60 * 1000;
            break;
        case 4:
            _waitForValueTimeoutMs = 2 * 60 * 60 * 1000;
            break;
        case 5:
            _waitForValueTimeoutMs = 3 * 60 * 60 * 1000;
            break;
        case 6:
            _waitForValueTimeoutMs = 4 * 60 * 60 * 1000;
            break;
        case 7:
            _waitForValueTimeoutMs = 8 * 60 * 60 * 1000;
            break;
        case 8:
            _waitForValueTimeoutMs = 12 * 60 * 60 * 1000;
            break;
    }
    setState(ValueMonitorWatchdogState::ValueMonitorWatchdogStateDisabled);
    

    if (!KoFCB_CHValueToLow.initialized())
        KoFCB_CHValueToLow.value(false, DPT_Switch);
    if (!KoFCB_CHValueToHigh.initialized())
        KoFCB_CHValueToHigh.value(false, DPT_Switch);
    if (!KoFCB_CHSummaryAlarm.initialized())
        KoFCB_CHSummaryAlarm.value(false, DPT_Switch);
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
                case ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorRequestValueAndIgnore:
                case ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorRequestValueAndProvideFallbackValue:
                    setState(ValueMonitorWatchdogState::ValueMonitorWatchdogStateWaitForResponseValue);
                    KoFCB_CHSInput.requestObjectRead();
                    break;
                default:
                    setState(ValueMonitorWatchdogState::ValueMonitorWatchdogStateWaitForTimeout);
                    break;
            }
        }
        else
        {
            KoFCB_CHSInput.requestObjectRead();
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
            default:
                break;
        }
    }
}

template <typename T>
void ValueMonitorBlock::handleInputKo(GroupObject &ko, T minValue, T maxValue)
{
    if (_watchDogState != ValueMonitorWatchdogState::ValueMonitorWatchdogStateDisabled)
    {
        _waitTimeStartMillis = max(1UL, millis());
        setState(ValueMonitorWatchdogState::ValueMonitorWatchdogStateWaitForTimeout);
    }
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
    if (isValid)
    {
        _lastValidValue = ko.value(_dpt);
        hasValidValue = true;
    }
    if (!hasSummaryAlarm)
    {
       hasSummaryAlarm = _watchDogState != ValueMonitorWatchdogStateDisabled;
    }
    if (hasSummaryAlarm)
    {
        KoFCB_CHSummaryAlarm.valueCompare(!isValid, DPT_Alarm);
    }
    KoFCB_CHValueReceiveTimeout.valueCompare(false, DPT_Switch);

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
    }

    if (toLow)
    {
        T replacementValue;
        //	<Enumeration Text="Überwachung deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Nichts senden" Value="1" Id="%ENID%" />
        // <Enumeration Text="Letzten gültigen Wert" Value="2" Id="%ENID%" />
        // <Enumeration Text="Grenzwert" Value="3" Id="%ENID%" />
        switch (ParamFCB_CHMonitoringMin)
        {
            case 2:
                if (!hasValidValue)
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
        T replacementValue;
        //	<Enumeration Text="Überwachung deaktiviert" Value="0" Id="%ENID%" />
        // <Enumeration Text="Nichts senden" Value="1" Id="%ENID%" />
        // <Enumeration Text="Letzten gültigen Wert" Value="2" Id="%ENID%" />
        // <Enumeration Text="Grenzwert" Value="3" Id="%ENID%" />
        switch (ParamFCB_CHMonitoringMax)
        {
            case 2:
                if (!hasValidValue)
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
        if (!hasValidValue)
            return;
        sendValue(_lastValidValue, true);
    }
    // Do not add code here, return happens early
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
    if (_watchDogState != ValueMonitorWatchdogState::ValueMonitorWatchdogStateDisabled)
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
        case ValueMonitorWatchdogState::ValueMonitorWatchdogStateWaitForTimeout:
            if (_waitForValueTimeoutMs > 0 && currentMillis - _waitTimeStartMillis > _waitForValueTimeoutMs)
            {
                switch (_watchDogFallbackBehaviour)
                {
                    case ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorRequestValueAndIgnore:
                    case ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorRequestValueAndProvideFallbackValue:
                        KoFCB_CHSInput.requestObjectRead();
                        setState(ValueMonitorWatchdogState::ValueMonitorWatchdogStateWaitForResponseValue);
                        break;
                    case ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorOnlyAlarm:
                        setAlarm = true;
                        break;
                    case ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorProvideFallbackValue:
                        sendFallbackValue = true;
                        setAlarm = true;
                        break;
                }
                _waitTimeStartMillis = max(1UL, millis());
            }
            break;
        case ValueMonitorWatchdogState::ValueMonitorWatchdogStateWaitForResponseValue:
            if (_waitForValueTimeoutMs > 0 && currentMillis - _waitTimeStartMillis > _waitForValueAfterReadTimeoutMs)
            {
                switch (_watchDogFallbackBehaviour)
                {
                    case ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorRequestValueAndProvideFallbackValue:
                    case ValueMonitorWatchdogFallbackBehavior::ValueMonitorWatchdogBehaviorProvideFallbackValue:
                        sendFallbackValue = true;
                        break;
                }
                setAlarm = true;
                _waitTimeStartMillis = max(1UL, millis());
                setState(ValueMonitorWatchdogState::ValueMonitorWatchdogStateWaitForTimeout);
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
            default:
                break;
        }
    }
}

void ValueMonitorBlock::setState(ValueMonitorWatchdogState state)
{
    _watchDogState = state;
}
