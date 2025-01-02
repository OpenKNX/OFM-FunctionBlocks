#pragma once
#include "OpenKNX.h"

class FunctionBlock : public OpenKNX::Channel
{
    std::string _name;
    uint16_t _koHasValue = 0;

  protected:
    FunctionBlock(uint8_t channelIndex, const char* name);
    GroupObject& getKo(uint8_t nr);
    bool hasValue(uint8_t nr);
    Dpt dptType(uint8_t typeParamValue);
  public:
    void setup(bool configured) override;
    const std::string name() override;
    virtual void readInputKos() = 0;
    virtual void initMissingInputValues() = 0;
    void processInputKo(GroupObject &ko);
    virtual void handleKo(GroupObject &ko) = 0;
    virtual bool processCommand(const std::string cmd, bool diagnoseKo);
};