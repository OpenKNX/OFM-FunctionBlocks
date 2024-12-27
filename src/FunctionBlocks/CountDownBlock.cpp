#include "CountDownBlock.h"
#define FCB_KoCHStoppStart FCB_KoCHKO0
#define KoFCB_CHStoppStart KoFCB_CHKO0

#define FCB_KoCHPauseContinue FCB_KoCHKO1
#define KoFCB_CHPauseContinue KoFCB_CHKO1

#define FCB_KoCHStartWithTime FCB_KoCHKO2
#define KoFCB_CHStartWithTime KoFCB_CHKO2

#define FCB_KoCHTimeOffset FCB_KoCHKO3
#define KoFCB_CHTimeOffset KoFCB_CHKO3

#define KoFCB_CHText KoFCB_CHKO5
#define KoFCB_CHPauseActive KoFCB_CHKO6
#define KoFCB_CHRemaining KoFCB_CHKO7
#define KoFCB_CHRunning KoFCB_CHKO8
#define KoFCB_CHTrigger KoFCB_CHKO9

CountDownBlock::CountDownBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "CountDown")
{
    // <Enumeration Id="%ENID%" Value="1"  Text="Nur EIN"             />
    // <Enumeration Id="%ENID%" Value="2"  Text="Ein für 1 Sekunde"  />
    // <Enumeration Id="%ENID%" Value="3"  Text="Ein für 2 Sekunden"  />
    // <Enumeration Id="%ENID%" Value="4"  Text="Ein für 5 Sekunden"  />
    // <Enumeration Id="%ENID%" Value="5"  Text="Ein für 10 Sekunden" />
    // <Enumeration Id="%ENID%" Value="6"  Text="Ein für 20 Sekunden" />
    // <Enumeration Id="%ENID%" Value="7"  Text="Ein für 30 Sekunden" />
    // <Enumeration Id="%ENID%" Value="8"  Text="Ein für 1 Minute"   />
    switch (ParamFCB_CHCountDownTrigger)
    {
        default:
            _triggerEnd = 0;
            break;
        case 1:
            _triggerEnd = -1;
            break;
        case 2:
            _triggerEnd = 1000;
            break;
        case 3:
            _triggerEnd = 2000;
            break;
        case 4:
            _triggerEnd = 5000;
            break;
        case 5:
            _triggerEnd = 10000;
            break;
        case 6:
            _triggerEnd = 20000;
            break;
        case 7:
            _triggerEnd = 30000;
            break;
        case 8:
            _triggerEnd = 60000;
            break;
    }

    KoFCB_CHPauseActive.value(false, DPT_Switch);
    KoFCB_CHRunning.value(false, DPT_Switch);
    if (_triggerEnd) // Trigger with time out
        KoFCB_CHTrigger.value(false, DPT_Switch);
    updateTextKo(0);
    updateRemainingKo();
}

void CountDownBlock::handleKo(GroupObject &ko)
{
    switch (FCB_KoCalcIndex(ko.asap()))
    {
        case FCB_KoCHStoppStart: {
            if (ko.value(DPT_Switch))
                start(knx.paramInt(FCB_ParamCalcIndex(FCB_CHCountDownStartValue)));
            else
                stop();
            break;
        }
        case FCB_KoCHStartWithTime: {
            uint8_t value = ko.value(DPT_Value_1_Ucount);
            // <Enumeration Id="%ENID%" Value="0"  Text="Deaktiviert"  />
            // <Enumeration Id="%ENID%" Value="1"  Text="Sekunden"  />
            // <Enumeration Id="%ENID%" Value="2"  Text="Minuten"   />
            // <Enumeration Id="%ENID%" Value="3"  Text="Stunden"   />
            switch (ParamFCB_CHCountDownTimeStartKo)
            {
                default:
                    return;
                case 1:
                    value *= 1;
                    break;
                case 2:
                    value *= 60;
                    break;
                case 3:
                    value *= 3600;
                    break;
            }
            start(value);
            break;
        }
        case FCB_KoCHTimeOffset: {
            bool down = ko.value(DPT_UpDown);
            // <Enumeration Id="%ENID%" Value="0"  Text="Deaktiviert"  />
            // <Enumeration Id="%ENID%" Value="1"  Text="1 Sekunde"    />
            // <Enumeration Id="%ENID%" Value="2"  Text="5 Sekunden"   />
            // <Enumeration Id="%ENID%" Value="3"  Text="10 Sekunden"  />
            // <Enumeration Id="%ENID%" Value="4"  Text="15 Sekunden"  />
            // <Enumeration Id="%ENID%" Value="5"  Text="30 Sekunden"  />
            // <Enumeration Id="%ENID%" Value="6"  Text="1 Minute"     />
            // <Enumeration Id="%ENID%" Value="7"  Text="5 Minuten"    />
            // <Enumeration Id="%ENID%" Value="8"  Text="10 Minuten"   />
            // <Enumeration Id="%ENID%" Value="9"  Text="15 Minuten"   />
            // <Enumeration Id="%ENID%" Value="10" Text="30 Minuten"   />
            // <Enumeration Id="%ENID%" Value="11" Text="1 Stunde"     />
            uint16_t value = 1;
            switch (ParamFCB_CHCountDownTimeOffset)
            {
                default:
                    return;
                case 1:
                    value = 1;
                    break;
                case 2:
                    value = 5;
                    break;
                case 3:
                    value = 10;
                    break;
                case 4:
                    value = 15;
                    break;
                case 5:
                    value = 30;
                    break;
                case 6:
                    value = 60;
                    break;
                case 7:
                    value = 300;
                    break;
                case 8:
                    value = 600;
                    break;
                case 9:
                    value = 900;
                    break;
                case 10:
                    value = 1800;
                    break;
                case 11:
                    value = 3600;
                    break;
            }
            if (down)
            {
                if (_remainingSeconds <= value)
                {
                    _targetSeconds -= _remainingSeconds;
                    _remainingSeconds = 0;
                    finished();
                }
                else
                {
                    _remainingSeconds -= value;
                    _targetSeconds -= value;
                    updateRemainingKo();
                    updateTextKo(true);
                }
            }
            else
            {
                if (_lastValueUpdate == 0)
                    start(value);
                else
                {
                    _remainingSeconds += value;
                    _targetSeconds += value;
                    updateRemainingKo();
                    updateTextKo(true);
                }
            }
            break;
        }
        case FCB_KoCHPauseContinue: {
            pause(ko.value(DPT_Switch));
            break;
        }
    }
}

void CountDownBlock::readInputKos()
{
}

void CountDownBlock::initMissingInputValues()
{
}

void CountDownBlock::start(uint64_t startValue)
{
    if (startValue == 0)
    {
        stop();
    }
    else
    {
        _lastValueUpdate = 0; // stop previous
        pause(false);
        _targetSeconds = startValue;
        _remainingSeconds = startValue;
        _lastValueUpdate = max(1ul, millis());
        updateRemainingKo();
        KoFCB_CHRunning.value(true, DPT_Switch);
        if (_triggerEnd) // Trigger with time out
            KoFCB_CHTrigger.valueCompare(false, DPT_Switch);

        updateTextKo(true);
    }
}

void CountDownBlock::pause(bool pause)
{
    if (pause != _pause)
    {
        if (_lastValueUpdate > 0) 
        {
            // running
            _pause = pause;
            KoFCB_CHPauseActive.value(pause, DPT_Switch);
            if (pause)
                _lastValueUpdate = max(1ul, millis() - _lastValueUpdate); // Store already elapsed time
            else
                _lastValueUpdate = max(1ul, millis() - _lastValueUpdate); // Start from now - already elapsed time
            updateTextKo(true);
        }
        else
        {
            _pause = false;
            KoFCB_CHPauseActive.value(false, DPT_Switch);
        }
    }
}

void CountDownBlock::stop()
{
    _lastValueUpdate = 0;
    _targetSeconds = 0;
    _remainingSeconds = 0;
    KoFCB_CHRunning.value(false, DPT_Switch);
    updateRemainingKo();
    updateTextKo(true);
    pause(false);
}

void CountDownBlock::loop()
{
    if (_waitForTriggerEnd > 0 && millis() - _waitForTriggerEnd > _triggerEnd)
    {
        KoFCB_CHTrigger.value(false, DPT_Switch);
        _waitForTriggerEnd = 0;
    }
    if (_lastValueUpdate > 0 && !_pause)
    {
        unsigned long now = millis();
        if (now - _lastValueUpdate >= 1000)
        {
            auto toLateOffest = now - _lastValueUpdate - 1000;
            if (_remainingSeconds > 0)
                _remainingSeconds--;
            else
                _remainingSeconds = 0;

            if (_remainingSeconds == 0)
                _lastValueUpdate = 0;
            else
                _lastValueUpdate = max(1ul, now - toLateOffest);

            updateRemainingKo();
            if (_lastValueUpdate == 0)
            {
                finished();
            }
            else
            {
                updateTextKo(false);
            }
        }
    }
}

void CountDownBlock::finished()
{
    KoFCB_CHRunning.value(false, DPT_Switch);
    auto trigger = ParamFCB_CHCountDownTrigger;
    if (trigger > 0)
        KoFCB_CHTrigger.value(true, DPT_Switch);
    if (trigger > 1) // Trigger with time out
        _waitForTriggerEnd = millis();
    updateTextKo(true, true);
}

void CountDownBlock::updateRemainingKo()
{
#ifdef OPENKNX_FCB_DEBUG
    logErrorP("Remaining seconds: %lu", _remainingSeconds);
    logErrorP("Running seconds: %lu", _targetSeconds - _remainingSeconds);
#endif
    auto remaining = _remainingSeconds;
    // <Enumeration Id="%ENID%" Value="0"  Text="Deaktiviert"  />
    // <Enumeration Id="%ENID%" Value="1"  Text="Verbleibend Sekunden (Zählt abwärts)" />
    // <Enumeration Id="%ENID%" Value="2"  Text="Verbleibend Minuten (Zählt abwärts)" />
    // <Enumeration Id="%ENID%" Value="3"  Text="Verbleibend Stunden (Zählt abwärts)" />
    // <Enumeration Id="%ENID%" Value="4"  Text="Vergangen Sekunden (Zählt aufwärts)" />
    // <Enumeration Id="%ENID%" Value="5"  Text="Vergangen Minuten (Zählt aufwärts)" />
    // <Enumeration Id="%ENID%" Value="6"  Text="Vergangen Stunden (Zählt aufwärts)" />
    switch (ParamFCB_CHCountDownCounterKo)
    {
        default:
            return;
        case 1:
            remaining = _remainingSeconds;
            break;
        case 2:
            remaining = ceil(_remainingSeconds / 60.F);
            break;
        case 3:
            remaining = ceil(_remainingSeconds / 3600.F);
            break;
        case 4:
            remaining = _targetSeconds - _remainingSeconds;
            break;
        case 5:
            remaining = ceil((_targetSeconds - _remainingSeconds) / 60.F);
            break;
        case 6:
            remaining = ceil((_targetSeconds - _remainingSeconds) / 3600.F);
            break;
    }
    KoFCB_CHRemaining.value(remaining, DPT_Value_1_Ucount);
}

void CountDownBlock::updateTextKo(bool forceSend, bool end)
{

    unsigned int value = _remainingSeconds;
    // <Enumeration Id="%ENID%" Value="0"  Text="Deaktiviert"  />
    // <Enumeration Id="%ENID%" Value="1"  Text="Verbleibend (Zählt abwärts)" />
    // <Enumeration Id="%ENID%" Value="2"  Text="Vergangen (Zählt aufwärts)" />
    switch (ParamFCB_CHCountDownTextKo)
    {
        default:
            return;
        case 1:
            break;
        case 2:
            value = _targetSeconds - _remainingSeconds;
            break;
    }
    const char *format = "";
    if (_remainingSeconds == 0)
    {
        if (end)
            format = (const char *)ParamFCB_CHCountDownTemplateEnd;
    }
    else if (_remainingSeconds <= 60)
    {
        format = (const char *)ParamFCB_CHCountDownTemplate1m;
    }
    else if (_remainingSeconds <= 3600)
    {
        format = (const char *)ParamFCB_CHCountDownTemplate1h;
    }
    else
    {
        format = (const char *)ParamFCB_CHCountDownTemplate;
    }

    unsigned int hours = 0;
    bool useMinutes = strstr(format, "M2") != nullptr || strstr(format, "M1") != nullptr;
    bool useSeconds = strstr(format, "S2") != nullptr || strstr(format, "S1") != nullptr || strstr(format, "S1") != nullptr;
    if (strstr(format, "H2") != nullptr || strstr(format, "H1") != nullptr)
    {
        if (useMinutes)
        {
            // round down
            hours = value / 3600;
            value -= hours * 3600;
        }
        else
        {
            // round up
            hours = ceil(value / 3600.F);
            auto seconds = hours * 3600;
            if (seconds > value)
                value -= seconds;
            else
                value = 0;
        }
    }
    unsigned int minutes = 0;
    if (useMinutes)
    {
        if (useSeconds)
        {
            // round down
            minutes = value / 60;
            value -= hours * 60;
        }
        else
        {
            // round up
            minutes = ceil(value / 60.F);
            auto seconds = hours * 60;
            if (seconds > value)
                value -= seconds;
            else
                value = 0;
        }
    }
    char buffer[15];
    int bufferIndex = 0;
    for (int i = 0; format[i] != '\0' && bufferIndex < 14; ++i)
    {
        char c = format[i];
        switch (c)
        {
            case '$':
                char cState;
                if (_pause)
                    cState = ((const char *)ParamFCB_CHCountDownTextPause)[0];
                else
                    cState = ((const char *)ParamFCB_CHCountDownTextRun)[0];
                if (cState != '\0')
                    buffer[bufferIndex++] = cState;
                break;
            case 'H':
                if (format[i + 1] == '2')
                {
                    bufferIndex += snprintf(buffer + bufferIndex, sizeof(buffer) - bufferIndex, "%02u", hours);
                    i++;
                }
                else if (format[i + 1] == '1')
                {
                    bufferIndex += snprintf(buffer + bufferIndex, sizeof(buffer) - bufferIndex, "%u", hours);
                    i++;
                }
                else
                {
                    buffer[bufferIndex++] = c;
                }
                break;
            case 'M':
                if (format[i + 1] == '2')
                {
                    bufferIndex += snprintf(buffer + bufferIndex, sizeof(buffer) - bufferIndex, "%02u", minutes);
                    i++;
                }
                else if (format[i + 1] == '1')
                {
                    bufferIndex += snprintf(buffer + bufferIndex, sizeof(buffer) - bufferIndex, "%u", minutes);
                    i++;
                }
                else
                {
                    buffer[bufferIndex++] = c;
                }
                break;
            case 'S':
                if (format[i + 1] == '2')
                {
                    bufferIndex += snprintf(buffer + bufferIndex, sizeof(buffer) - bufferIndex, "%02u", value);
                    i++;
                }
                else if (format[i + 1] == '1')
                {
                    bufferIndex += snprintf(buffer + bufferIndex, sizeof(buffer) - bufferIndex, "%u", value);
                    i++;
                }
                else if (format[i + 1] == 'X')
                {
                    unsigned int seconds10 = ceil(value / 10.F);
                    bufferIndex += snprintf(buffer + bufferIndex, sizeof(buffer) - bufferIndex, "%u0", seconds10);
                    i++;
                }
                else
                {
                    buffer[bufferIndex++] = c;
                }
                break;

            default:
                buffer[bufferIndex++] = c;
        }
    }
    buffer[bufferIndex] = '\0';
    if (forceSend)
        KoFCB_CHText.value(buffer, DPT_String_8859_1);
    else
        KoFCB_CHText.valueCompare(buffer, DPT_String_8859_1);
}
#ifdef OPENKNX_FCB_DEBUG
bool CountDownBlock::processCommand(const std::string cmd, bool diagnoseKo)
{
    if (cmd == "start")
    {
        KoFCB_CHStoppStart.valueNoSend(true, DPT_Switch);
        handleKo(KoFCB_CHStoppStart);
        return true;
    }
    else if (cmd.rfind("start ", 0) == 0)
    {
        std::string value = cmd.substr(6);
        uint8_t startValue = 0;
        if (value == "0")
        {
            startValue = 0;
        }
        else
        {
            startValue = atoi(value.c_str());
        }
        KoFCB_CHStartWithTime.valueNoSend(startValue, DPT_Value_1_Ucount);
        handleKo(KoFCB_CHStartWithTime);
        return true;
    }
    else if (cmd == "pause")
    {
        KoFCB_CHPauseContinue.valueNoSend(true, DPT_Switch);
        handleKo(KoFCB_CHPauseContinue);
        return true;
    }
    else if (cmd == "continue")
    {
        KoFCB_CHPauseContinue.valueNoSend(false, DPT_Switch);
        handleKo(KoFCB_CHPauseContinue);
        return true;
    }
    else if (cmd == "stop")
    {
        KoFCB_CHStoppStart.valueNoSend(false, DPT_Switch);
        handleKo(KoFCB_CHStoppStart);
        return true;
    }
    else if (cmd == "up")
    {
        if (ParamFCB_CHCountDownTimeOffset == 0)
        {
            logErrorP("Ko Laufzeit Verringern / Erhöhen nicht aktiviert");
        }
        else
        {
            KoFCB_CHTimeOffset.valueNoSend(false, DPT_UpDown);
            handleKo(KoFCB_CHTimeOffset);
        }
        return true;
    }
    else if (cmd == "down")
    {
        if (ParamFCB_CHCountDownTimeOffset == 0)
        {
            logErrorP("Ko Laufzeit Verringern / Erhöhen nicht aktiviert");
        }
        else
        {
            KoFCB_CHTimeOffset.valueNoSend(true, DPT_UpDown);
            handleKo(KoFCB_CHTimeOffset);
        }
        return true;
    }
    return false;
}
#endif