#pragma once
#include "OpenKNX.h"
#include "FunctionBlocks/ValueMonitorBlock.h"

#define OPENKNX_LEDFUNC_FB_VALUE_MONITOR 401

class LedFunctionValueMonitor
{
#ifdef OPENKNX_LEDFUNC_BASE_TIME
    OpenKNX::Led::FunctionGroup* _ledFunctionGroup = nullptr;
    ValueMonitorAlarmState _lastAlarmState = (ValueMonitorAlarmState) 255;
#endif
public:
    void loop();
};

