#include "LedFunctionTimeStateSeconds.h"


void LedFunctionTimeStateSeconds::loop()
{
#ifdef OPENKNX_LEDFUNC_BASE_TIME
    if (_ledFunctionGroup == nullptr)
    {
        openknx.time.registerCallback(OpenKNX::Time::TimeChangedEvents::TimeChangedEventTimeSet, [this](OpenKNX::Time::TimeChangedArgs args) {
        _timeSetTimeStamp = millis();
        });
        _ledFunctionGroup = openknx.ledFunctions.get(OPENKNX_LEDFUNC_FB_TIME_SECOND_STATE);
    }
    if (_timeSetTimeStamp != 0)
    {
        _ledFunctionGroup->color(OpenKNX::Led::Color::Green);
        _ledFunctionGroup->on(OpenKNX::Led::Capability::COLOR);
        _ledFunctionGroup->blinking(100, OpenKNX::Led::Capability::MONOCHROME);
        if (delayCheck(_timeSetTimeStamp, 1000))
        {
            _timeSetTimeStamp = 0;
        }
    }
    else if (openknx.time.isValid())
    {
        auto localTime = openknx.time.getLocalTime();
        auto inaccurate = openknx.time.isInaccurate();
        uint8_t phase = localTime.second % (inaccurate ? 4 : 2);
        if (phase < 1) 
        {
            _ledFunctionGroup->color(inaccurate ? OpenKNX::Led::Color::Yellow : OpenKNX::Led::Color::Blue);
            _ledFunctionGroup->on();
        } 
        else
        {                
            _ledFunctionGroup->off();
        }
    }
    else
    {
        // time is invalid
        _ledFunctionGroup->color(OpenKNX::Led::Color::Red);
        _ledFunctionGroup->on(OpenKNX::Led::Capability::COLOR);
        _ledFunctionGroup->off(OpenKNX::Led::Capability::MONOCHROME);
    }
#endif
}
