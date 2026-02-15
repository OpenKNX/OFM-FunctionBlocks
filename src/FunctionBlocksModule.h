#pragma once
#include "knxprod.h"
#ifndef ParamFCB_CHFormatStringStr
#error "OpenKNXproducer 3.12.8.0 or higher is required to compile this project. Please update your OpenKNXproducer installation."
#endif
#include "OpenKNX.h"
#include "ChannelOwnerModule.h"
#include "LedFunctionTimeStateSeconds.h"
#include "LedFunctionValueMonitor.h"

class FunctionBlocksModule : public FCBChannelOwnerModule
{
   
    unsigned int _startTime = 0;
    LedFunctionTimeStateSeconds _statusLedTimeStateSeconds;
    LedFunctionValueMonitor _statusLedValueMonitor;
  #ifdef OPENKNX_LEDFUNC_BASE_PROG_UNCONFIGUREDSUPPORT
    class DummyLedToGetCurrentState : public OpenKNX::Led::Base
    {
      public:
        unsigned long progLedLastOff = millis();
        bool isOff = true;;
        void writeLed(uint8_t brightness) override 
        {
          isOff = brightness == 0;
          if (isOff)
          { 
            progLedLastOff = millis();
          }
        }
        void init() override { _initialized = true; }
    };
    OpenKNX::Led::FunctionGroup* _ledProgLedFunctionGroup;
    DummyLedToGetCurrentState* _dummyLed;
    unsigned long _lastBlink = 0;
    int _blinkState = 0;
  #endif
  public:
    FunctionBlocksModule();
    const std::string name() override;
    void showInformations() override;
    const std::string version() override;
    void setup(bool configured) override;
    OpenKNX::Channel* createChannel(uint8_t _channelIndex /* this parameter is used in macros, do not rename */) override;
    void showHelp() override;
    bool processCommand(const std::string cmd, bool diagnoseKo) override;
    void loop(bool configured) override;
};

extern FunctionBlocksModule openknxFunctionBlocksModule;