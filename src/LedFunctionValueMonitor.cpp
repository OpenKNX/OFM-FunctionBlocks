#include "LedFunctionValueMonitor.h"
#include "FunctionBlocks/ValueMonitorBlock.h"



void LedFunctionValueMonitor::loop()
{
#ifdef OPENKNX_LEDFUNC_BASE_TIME
    if (_ledFunctionGroup == nullptr)
    {
        _ledFunctionGroup = openknx.ledFunctions.get(OPENKNX_LEDFUNC_FB_VALUE_MONITOR);
    }
    auto valueMonitorInstances = ValueMonitorBlock::getInstances();
    int intanceCount = 0;
    ValueMonitorAlarmState sumAlarmState = ValueMonitorAlarmState::NoAlarm;
    for (const auto& instance : valueMonitorInstances)
    {
        intanceCount++;
        auto alarmState = instance->alarmState();
        if (alarmState > sumAlarmState)
        {
           sumAlarmState = alarmState;
        }
    }
    if (sumAlarmState != _lastAlarmState)
    {
        _lastAlarmState = sumAlarmState;
        // logDebug("LedFunctionValueMonitor", "LedFunctionValueMonitor of %d instances: Updating LED state to alarm state %u", intanceCount, static_cast<uint8_t>(sumAlarmState));

        switch (sumAlarmState)
        {
            case ValueMonitorAlarmState::NoAlarm:
                _ledFunctionGroup->color(OpenKNX::Led::Color::Green);
                _ledFunctionGroup->on(OpenKNX::Led::Capability::COLOR);
                _ledFunctionGroup->off(OpenKNX::Led::Capability::MONOCHROME);
                break;
            case ValueMonitorAlarmState::WaitForValue:
                _ledFunctionGroup->color(OpenKNX::Led::Color::Yellow);
                _ledFunctionGroup->on(OpenKNX::Led::Capability::COLOR);
                _ledFunctionGroup->blinking(500, OpenKNX::Led::Capability::MONOCHROME);
                break;
            case ValueMonitorAlarmState::ValueTooLow:
                _ledFunctionGroup->color(OpenKNX::Led::Color::Blue);
                _ledFunctionGroup->on(OpenKNX::Led::Capability::COLOR);
                _ledFunctionGroup->blinking(200, OpenKNX::Led::Capability::MONOCHROME);
                break;
            case ValueMonitorAlarmState::ValueTooHigh:
                _ledFunctionGroup->color(OpenKNX::Led::Color::Orange);
                _ledFunctionGroup->on(OpenKNX::Led::Capability::COLOR);
                _ledFunctionGroup->blinking(100, OpenKNX::Led::Capability::MONOCHROME);
                break;
            case ValueMonitorAlarmState::Timeout:
                _ledFunctionGroup->color(OpenKNX::Led::Color::Red);
                _ledFunctionGroup->on();
                break;
        }
    }
#endif
}
