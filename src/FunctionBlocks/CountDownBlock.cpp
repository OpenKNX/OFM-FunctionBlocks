#include "CountDownBlock.h"
#define FCB_CHStoppStart FCB_KoCHKO0
#define FCB_CHPauseContinue FCB_KoCHKO1
#define FCB_CHStartWithTime FCB_KoCHKO2

#define KoFCB_CHText KoFCB_CHKO6
#define KoFCB_CHPauseActive KoFCB_CHKO7
#define KoFCB_CHRemaining KoFCB_CHKO8
#define KoFCB_CHRunning KoFCB_CHKO9

CountDownBlock::CountDownBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "CountDown")
{
    // <Enumeration Id="%ENID%" Value="0"  Text="Sekunden"                           />
    // <Enumeration Id="%ENID%" Value="1"  Text="Minuten"                            />
    // <Enumeration Id="%ENID%" Value="2"  Text="Stunden"                            />
    switch (ParamFCB_CHCountDownUnit)
    {
        case 0:
            _countValue = 1000;
            break;
        case 1:
            _countValue = 60 * 1000;
            break;
        case 2:
            _countValue = 60 * 60 * 1000;
            break;
    }
    KoFCB_CHRemaining.value(0ul, DPT_Value_1_Ucount);
    KoFCB_CHPauseActive.value(false, DPT_Switch);
    KoFCB_CHRunning.value(false, DPT_Switch);
    updateText(0);    
}

void CountDownBlock::handleKo(GroupObject &ko)
{
    switch (ko.asap())
    {
        case FCB_CHStoppStart:
            if (ko.value(DPT_Switch))
                start(ParamFCB_CHFCBCountDownStartValue);
            else
                stop();
            break;
        case FCB_CHPauseContinue:
            pause(ko.value(DPT_Switch));
            break;
        case FCB_CHStartWithTime:
            start(ko.value(DPT_Value_1_Ucount));
            break;
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
        _lastValueUpdate = max(1ul, millis());
        KoFCB_CHRemaining.value(startValue, DPT_Value_1_Ucount);
        KoFCB_CHRunning.value(true, DPT_Switch);
        updateText(startValue);
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
            uint64_t value = KoFCB_CHRemaining.value(DPT_Value_1_Ucount);
            updateText(value);
        }
    }
}

void CountDownBlock::stop()
{
    _lastValueUpdate = 0;
    KoFCB_CHRunning.value(false, DPT_Switch);
    KoFCB_CHText.value("Gestoppt", DPT_String_8859_1);
}

void CountDownBlock::loop()
{
    if (_lastValueUpdate > 0 && !_pause)
    {
        unsigned long now = millis();
        if (now - _lastValueUpdate >= _countValue)
        {
            auto toLateOffest = now - _lastValueUpdate;
            uint64_t value = KoFCB_CHRemaining.value(DPT_Value_1_Ucount);
            if (value > 0)
                value--;
            else
                value = 0;

            if (value == 0)
                _lastValueUpdate = 0;
            else
                _lastValueUpdate = max(1ul, now - toLateOffest);

            KoFCB_CHRemaining.value(value, DPT_Value_1_Ucount);
            if (_lastValueUpdate == 0)
            {
                KoFCB_CHRunning.value(false, DPT_Switch);
                KoFCB_CHText.value("Ende", DPT_String_8859_1);
            }
            else
            {
                updateText(value);
            }
        }
    }
}

void CountDownBlock::updateText(uint64_t value)
{
    if (_lastValueUpdate == 0)
    {
        KoFCB_CHText.value("Gestoppt", DPT_String_8859_1);
        return;
    }
    char buffer[15] = {0};
    const char *unit = "";
    switch (ParamFCB_CHCountDownUnit)
    {
        case 0:
            unit = "s";
            break;
        case 1:
            unit = "m";
            break;
        case 2:
            unit = "h";
            break;
    }
    const char* pauseText = "";
    if (_pause)
        pauseText = " Pause";
    snprintf(buffer, sizeof(buffer), "%lu %s%s", value, unit, pauseText);
    KoFCB_CHText.value(buffer, DPT_String_8859_1);
}