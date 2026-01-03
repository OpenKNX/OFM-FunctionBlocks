#pragma once
#include "OpenKNX.h"

#define OPENKNX_LEDFUNC_FB_TIME_SECOND_STATE 400

class LedFunctionTimeStateSeconds 
{
#ifdef OPENKNX_LEDFUNC_BASE_TIME
    OpenKNX::Led::FunctionGroup* _ledFunctionGroup = nullptr;
    uint8_t _lastSecondChange = 255;
    unsigned long _timeSetTimeStamp = 0;
    unsigned long _timerLedOn = 0;
#endif
public:
    void loop();
};

