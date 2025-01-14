#include "BlinkerBlock.h"

#define FCB_KoCHStoppStart FCB_KoCHKO0
#define KoFCB_CHStoppStart KoFCB_CHKO0
#define FCB_KoCHStartWithCount FCB_KoCHKO1
#define KoFCB_CHStartWithCount KoFCB_CHKO1
#define FCB_KoCHActorFeedback FCB_KoCHKO2
#define KoFCB_CHActorFeedback KoFCB_CHKO2

#define KoFCB_CHBlinkingActive KoFCB_CHKO8
#define KoFCB_CHOutput KoFCB_CHKO9

BlinkerBlock::BlinkerBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "Blinker")
{
    // <Enumeration Text="Immer" Value="255" Id="%ENID%" />
    if (ParamFCB_CHBlinkerCount == 255)
    {
        _hasActorFeedbackKO = false;
        start();
    }
    else
    {
         _hasActorFeedbackKO = true;
    }
}

void BlinkerBlock::handleKo(GroupObject &ko)
{
    switch (FCB_KoCalcIndex(ko.asap()))
    {
        case FCB_KoCHStoppStart: {
            if (ko.value(DPT_Switch))
            {
                // <Enumeration Text="Solange Start EIN" Value="0" Id="%ENID%" />
                auto maxBlink = ParamFCB_CHBlinkerCount;
                start(maxBlink);
            }
            else
            {
                breakRequest();
            }
            break;
        }
        break;
        case FCB_KoCHStartWithCount: {
             // <Enumeration Text="Solange Start EIN" Value="0" Id="%ENID%" />
            if (ParamFCB_CHBlinkerCount == 0 && _onOffChangeCount == 0 && _lastChange != 0)  
            {
                // On through KO, ignore input
                break;
            }
            uint8_t count = ko.value(DPT_Value_1_Ucount);
            if (count > 0)
            {
                start(count);
            }
            else
            {
                breakRequest();
            }
            break;
        }
    }
}

void BlinkerBlock::start(uint8_t count)
{
    GroupObject &goState = _hasActorFeedbackKO && KoFCB_CHActorFeedback.initialized() ? KoFCB_CHActorFeedback : KoFCB_CHOutput;
    bool currentOn = false;
    if (goState.initialized())
    {
        if (ParamFCB_CHBlinkerOutputDpt == 51)
        {
            _startValue = goState.value(DPT_Scaling);
            currentOn = _startValue != ParamFCB_CHBlinkerOffPercentage;
        }
        else
        {
            _isOn = goState.value(DPT_Switch);
            currentOn = _isOn;
        }
    }
    else
    {
        if (ParamFCB_CHBlinkerOutputDpt == 51)
        {
            _startValue = ParamFCB_CHBlinkerOffPercentage;
            currentOn = false;
        }
        else
        {
            _startValue = 0;
            currentOn = false;
        }
    }
   
    _lastChange = max(millis(), 1ul);
    // <Enumeration Text="Mit EIN starten" Value="1" Id="%ENID%" />
    // <Enumeration Text="Mit AUS starten" Value="0" Id="%ENID%" />
    // <Enumeration Text="Umgekehrt zur aktuellen Aktor Rückmeldung" Value="2" Id="%ENID%" />
    switch (ParamFCB_CHBlinkerStart)
    {
        case 0:
            _isOn = false;
            break;
        case 1:
            _isOn = true;
            break;
        case 2:
            _isOn = !currentOn;
            break;
    }
    // <Enumeration Text="Immer" Value="255" Id="%ENID%" />
    // <Enumeration Text="Solange Start EIN" Value="0" Id="%ENID%" />
    auto maxBlink = ParamFCB_CHBlinkerCount;
    if (maxBlink != 255 && (maxBlink != 0 || count != 0))
    {
        _onOffChangeCount = count * 2;

        // <Enumeration Text="Mit EIN beenden" Value="1" Id="%ENID%" />
        // <Enumeration Text="Mit AUS beenden" Value="0" Id="%ENID%" />
        // <Enumeration Text="Wie Zustand vor Blink-Beginn" Value="2" Id="%ENID%" />
        // <Enumeration Text="Umgekehrt wie Zustand vor Blink-Beginn" Value="3" Id="%ENID%" />
        switch (ParamFCB_CHBlinkerStop)
        {
            case 0:
                if (_isOn)
                    _onOffChangeCount--; // Skip last half phase
                break;
            case 1:
                if (!_isOn)
                    _onOffChangeCount--; // Skip last half phase
                break;
            case 2:
                if (_isOn != currentOn)
                    _onOffChangeCount--; // Skip last half phase
                break;
            case 3:
                if (_isOn == currentOn)
                    _onOffChangeCount--; // Skip last half phase
                break;
        }
    }
    else
    {
        _onOffChangeCount = 0;
    }

    KoFCB_CHBlinkingActive.value(true, DPT_Switch);
    setOutput(_isOn);
}

void BlinkerBlock::setOutput(bool value)
{
    if (ParamFCB_CHBlinkerOutputDpt == 51)
    {
        uint8_t percentageValue = value ? ParamFCB_CHBlinkerOnPercentage : ParamFCB_CHBlinkerOffPercentage;
        KoFCB_CHOutput.value(percentageValue, DPT_Scaling);
        KoFCB_CHActorFeedback.valueNoSend(percentageValue, DPT_Scaling);
    }
    else
    {
        KoFCB_CHOutput.value(value, DPT_Switch);
        KoFCB_CHActorFeedback.valueNoSend(value, DPT_Switch);
    }
}

void BlinkerBlock::setOutputToStartValue()
{
    if (ParamFCB_CHBlinkerOutputDpt == 51)
    {
        uint8_t percentageValue = _startValue;
        KoFCB_CHOutput.value(percentageValue, DPT_Scaling);
        KoFCB_CHActorFeedback.valueNoSend(percentageValue, DPT_Scaling);
    }
    else
    {
        bool value = _startValue;
        KoFCB_CHOutput.value(value, DPT_Switch);
        KoFCB_CHActorFeedback.valueNoSend(value, DPT_Switch);
    }
}

void BlinkerBlock::breakRequest()
{

    // <Enumeration Text="Ignorieren" Value="0" Id="%ENID%" />
    // <Enumeration Text="Blinken sofort beenden und EIN senden" Value="1" Id="%ENID%" />
    // <Enumeration Text="Blinken sofort beenden und AUS senden" Value="2" Id="%ENID%" />
    // <Enumeration Text="Blinken sofort beenden, Zustand vor Blink-Beginn herstellen" Value="3" Id="%ENID%" />
    // <Enumeration Text="Blinken sofort beenden, Zustand umgekehrt wie vor Blink-Beginn herstellen" Value="4" Id="%ENID%" />
    // <Enumeration Text="Mit aktuellen Zustand beenden (Kein Telegram senden)" Value="5" Id="%ENID%" />
    switch (ParamFCB_CHBlinkerCount == 0 ? ParamFCB_CHBlinkerBreakWithoutBreak : ParamFCB_CHBlinkerBreak)
    {
        case 0:
            break;
        case 1:
            stop();
            setOutput(true);
            break;
        case 2:
            stop();
            setOutput(false);
            break;
        case 3:
            stop();
            setOutputToStartValue();
            break;
        case 4:
            stop();
            if (ParamFCB_CHBlinkerOutputDpt == 51)
            {
                setOutput(_startValue == ParamFCB_CHBlinkerOffPercentage);
            }
            else
            {
                setOutput(!_startValue);
            }
            break;
        case 5:
            stop();
            break;
    }
}

void BlinkerBlock::stop()
{
    KoFCB_CHBlinkingActive.value(false, DPT_Switch);
    _lastChange = 0;
    _onOffChangeCount = 0;
}

void BlinkerBlock::loop()
{
    if (_lastChange != 0)
    {
        unsigned long now = millis();
        auto time =  _isOn ? ParamFCB_CHBlinkerOnDelayTimeMS : ParamFCB_CHBlinkerOffDelayTimeMS;
        if (now - _lastChange >= time)
        {
            auto missed = now - _lastChange - time;
            _lastChange = max(now - missed, 1ul);
            _isOn = !_isOn;
            if (_onOffChangeCount != 0)
            {
                _onOffChangeCount--;
                if (_onOffChangeCount == 0)
                {
                    // <Enumeration Text="Mit EIN beenden" Value="1" Id="%ENID%" />
                    // <Enumeration Text="Mit AUS beenden" Value="0" Id="%ENID%" />
                    // <Enumeration Text="Wie Zustand vor Blink-Beginn" Value="2" Id="%ENID%" />
                    // <Enumeration Text="Umgekehrt wie Zustand vor Blink-Beginn" Value="3" Id="%ENID%" />
                    switch (ParamFCB_CHBlinkerStop)
                    {
                        case 0:
                            stop();
                            setOutput(false);
                            break;
                        case 1:
                            stop();
                            setOutput(true);
                            break;
                        case 2:
                            stop();
                            setOutputToStartValue();
                            break;
                        case 3:
                            stop();
                            if (ParamFCB_CHBlinkerOutputDpt == 51)
                            {
                                setOutput(_startValue == ParamFCB_CHBlinkerOffPercentage);
                            }
                            else
                            {
                                setOutput(!_startValue);
                            }
                            break;
                    }
                }
                else
                {
                    setOutput(_isOn);
                }
            }
            else
            {
                // Blinking always on
                setOutput(_isOn);
            }
        }
    }
}

void BlinkerBlock::readInputKos()
{
    if (_hasActorFeedbackKO && !KoFCB_CHActorFeedback.initialized())
        KoFCB_CHActorFeedback.requestObjectRead();
}

void BlinkerBlock::initMissingInputValues()
{
}
