#include "BlinkerBlock.h"

#define FCB_KoCHStoppStart FCB_KoCHKO0
#define KoFCB_CHStoppStart KoFCB_CHKO0
#define FCB_KoCHActorFeedback FCB_KoCHKO1
#define KoFCB_CHActorFeedback KoFCB_CHKO1

#define KoFCB_CHBlinkingActive KoFCB_CHKO8
#define KoFCB_CHOutput KoFCB_CHKO9

BlinkerBlock::BlinkerBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "Blinker")
{
    // <Enumeration Text="Immer" Value="255" Id="%ENID%" />					
    if (ParamFCB_CHBlinkerCount != 255)
    {
        _hasActorFeedbackKO =false;
        start();
    }
}

void BlinkerBlock::handleKo(GroupObject &ko)
{
    switch (FCB_KoCalcIndex(ko.asap()))
    {
        case FCB_KoCHStoppStart: {
            if (ko.value(DPT_Switch))
            {
                start();
            }
            else
            {
                breakRequest();
            }
            break;
        }
        break;
    }
}

void BlinkerBlock::start()
{
    GroupObject &goState = _hasActorFeedbackKO && KoFCB_CHActorFeedback.initialized() ? KoFCB_CHActorFeedback : KoFCB_CHOutput;
    if (goState.initialized())
    {
        if (ParamFCB_CHBlinkerOutputDpt == 51)
        {
            _startValue = goState.value(DPT_Scaling);
            _isOn = _startValue == ParamFCB_CHBlinkerOffPercentage;
        }
        else
        {
            _isOn = goState.value(DPT_Switch);
            _startValue = _isOn;
        }
    }
    else
    {
        if (ParamFCB_CHBlinkerOutputDpt == 51)
        {
            _startValue = ParamFCB_CHBlinkerOffPercentage;
            _isOn = false;
        }
        else
        {
            _startValue = 0;
            _isOn = false;
        }
    }
    _blinkCounter = 0;

    // <Enumeration Text="Mit EIN beenden" Value="1" Id="%ENID%" />
    // <Enumeration Text="Mit AUS beenden" Value="0" Id="%ENID%" />
    // <Enumeration Text="Wie Zustand vor Blink-Beginn" Value="2" Id="%ENID%" />
    // <Enumeration Text="Umgekehrt wie Zustand vor Blink-Beginn" Value="3" Id="%ENID%" />
    switch (ParamFCB_CHBlinkerStop)
    {
        case 0:
            if (_isOn)
                _blinkCounter++; // Skip last half phase
            break;    
        case 1:
            if (!_isOn)
                _blinkCounter++; // Skip last half phase
            break;
        case 2:
            _blinkCounter++; // Skip last half phase
            break;
    }
        
    _phaseStart = max(millis(), 1ul);
    // <Enumeration Text="Mit EIN starten" Value="1" Id="%ENID%" />
    // <Enumeration Text="Mit AUS starten" Value="0" Id="%ENID%" />
    // <Enumeration Text="Abhängig von aktueller Aktor Rückmeldung" Value="2" Id="%ENID%" />
    switch (ParamFCB_CHBlinkerStart)
    {
        case 0:
            _isOn = true;
            break;
        case 1:
            _isOn = false;
            break;
        case 2:
            _isOn = !_isOn;
            break;
    }
    KoFCB_CHBlinkingActive.value(true, DPT_Switch);
    setOutput(_isOn);
}

void BlinkerBlock::setOutput(bool value)
{
    if (ParamFCB_CHBlinkerOutputDpt == 51)
    {
        KoFCB_CHOutput.value(value ? ParamFCB_CHBlinkerOnPercentage : ParamFCB_CHBlinkerOffPercentage, DPT_Scaling);
    }
    else
    {
        KoFCB_CHOutput.value(value, DPT_Switch);
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
    switch (ParamFCB_CHBlinkerBreak)
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
            setOutput(_startValue);
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
    _phaseStart = 0;
    _blinkCounter = 0;
}

void BlinkerBlock::loop()
{
    if (_phaseStart != 0)
    {
        unsigned long now = millis();
        if (now - _phaseStart > _isOn ? ParamFCB_CHBlinkerOnDelayTimeMS : ParamFCB_CHBlinkerOffDelayTimeMS)
        {
            _phaseStart = max(now, 1ul);
            _isOn = !_isOn;
           _blinkCounter++;
            auto maxBlink = ParamFCB_CHBlinkerCount;
            // <Enumeration Text="Immer" Value="255" Id="%ENID%" />
            // <Enumeration Text="Solange Start EIN" Value="0" Id="%ENID%" />
            if (maxBlink != 255 && _blinkCounter != 0 && _blinkCounter == maxBlink * 2)
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
                        setOutput(_startValue);
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
