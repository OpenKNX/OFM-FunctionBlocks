#include "CountDownBlock.h"
#define FCB_KoCHStoppStart FCB_KoCHKO0
#define FCB_KoCHPauseContinue FCB_KoCHKO1
#define FCB_KoCHStartWithTime FCB_KoCHKO2
#define FCB_KoCHTimeOffset FCB_KoCHKO3

#define KoFCB_CHText KoFCB_CHKO5
#define KoFCB_CHPauseActive KoFCB_CHKO6
#define KoFCB_CHRemaining KoFCB_CHKO7
#define KoFCB_CHRunning KoFCB_CHKO8
#define KoFCB_CHTrigger KoFCB_CHKO9

CountDownBlock::CountDownBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "CountDown")
{
    KoFCB_CHRemaining.value(0ul, DPT_Value_1_Ucount);
    KoFCB_CHPauseActive.value(false, DPT_Switch);
    KoFCB_CHRunning.value(false, DPT_Switch);
    KoFCB_CHText.value("", DPT_String_8859_1);
    auto trigger = ParamFCB_CHCountDownTrigger;
    if (trigger > 1) // Trigger with time out
        KoFCB_CHTrigger.value(false, DPT_Switch);
    updateTextKo(0);
}

void CountDownBlock::handleKo(GroupObject &ko)
{
    switch (ko.asap())
    {
        case FCB_KoCHStoppStart: {
            if (ko.value(DPT_Switch))
                start(*(uint32_t *)knx.paramData(FCB_ParamCalcIndex(FCB_CHCountDownStartValue)));
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
            bool up = ko.value(DPT_UpDown);
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
            if (up)
            {
                if (_lastValueUpdate == 0)
                    start(value);
                else
                    _remainingSeconds += value;
            }
            else
            {
                if (_remainingSeconds <= value)
                    stop();
                else
                    _remainingSeconds -= value;
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
        if (!_pause)
            _lastValueUpdate = max(1ul, millis());
        updateRemainingKo();
        KoFCB_CHRunning.value(true, DPT_Switch);
        auto trigger = ParamFCB_CHCountDownTrigger;
        if (trigger > 1) // Trigger with time out
            KoFCB_CHTrigger.valueCompare(false, DPT_Switch);

        updateTextKo(true);
    }
}

void CountDownBlock::pause(bool pause)
{
    if (pause != _pause)
    {
        _pause = pause;
        KoFCB_CHPauseActive.value(pause, DPT_Switch);
        if (_lastValueUpdate > 0)
        {
            if (pause)
            {
                _lastValueUpdate = millis() - _lastValueUpdate; // Store already elapsed time
            }
            else
            {
                _lastValueUpdate = max(1ul, millis() + _lastValueUpdate); // Start from now - already elapsed time
            }
            updateTextKo(true);
        }
    }
}

void CountDownBlock::stop()
{
    _lastValueUpdate = 0;
    KoFCB_CHRunning.value(false, DPT_Switch);
    updateTextKo(true);
}

void CountDownBlock::loop()
{
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
                KoFCB_CHRunning.value(false, DPT_Switch);
                KoFCB_CHTrigger.value(true, DPT_Switch);
                updateTextKo(true, true);
            }
            else
            {
                updateTextKo(false);
            }
        }
    }
}

void CountDownBlock::updateRemainingKo()
{
    // ToDo: Handling of remaining unit
    KoFCB_CHRemaining.value(_remainingSeconds, DPT_Value_1_Ucount);
}

void CountDownBlock::updateTextKo(bool forceSend, bool end)
{
    // ToDo: Add template handling
    char buffer[15] = {0};
    // snprintf(buffer, sizeof(buffer), "%lu %s%s", value, unit, pauseText);
    if (forceSend)
        KoFCB_CHText.value(buffer, DPT_String_8859_1);
    else
        KoFCB_CHText.valueCompare(buffer, DPT_String_8859_1);
}