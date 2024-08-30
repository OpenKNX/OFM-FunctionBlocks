#pragma once
#include "OpenKNX.h"
#include "ChannelOwnerModule.h"

class FunctionBlocksModule : public FCBChannelOwnerModule
{
    unsigned int _startTime = 0;
  public:
    FunctionBlocksModule();
    const std::string name() override;
    const std::string version() override;
    void setup(bool configured) override;
    OpenKNX::Channel* createChannel(uint8_t _channelIndex /* this parameter is used in macros, do not rename */) override;
    void showHelp() override;
    bool processCommand(const std::string cmd, bool diagnoseKo) override;
    void loop() override;
};

extern FunctionBlocksModule openknxFunctionBlocksModule;