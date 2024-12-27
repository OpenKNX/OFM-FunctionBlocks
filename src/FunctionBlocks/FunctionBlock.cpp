#include "FunctionBlock.h"


FunctionBlock::FunctionBlock(uint8_t channelIndex, const char* name)
{
    _channelIndex = channelIndex;
    _name = name;
}

void FunctionBlock::setup(bool configured)
{
    OpenKNX::Channel::setup(configured);
    readInputKos();
}

const std::string FunctionBlock::name()
{
    return _name;
}

GroupObject& FunctionBlock::getKo(uint8_t nr)
{
    switch (nr)
    {
        case 0:
            return KoFCB_CHKO0;
        case 1:
            return KoFCB_CHKO1;
        case 2:
            return KoFCB_CHKO2;
        case 3:
            return KoFCB_CHKO3;
        case 4:
            return KoFCB_CHKO4;
        case 5:
            return KoFCB_CHKO5;
        case 6:
            return KoFCB_CHKO6;
        case 7:
            return KoFCB_CHKO7;
        case 8:
            return KoFCB_CHKO8;
        default:
            openknx.hardware.fatalError(FATAL_SYSTEM, "Invalid Ko");    
            return KoFCB_CHKO0;
    }
}

bool FunctionBlock::hasValue(uint8_t nr)
{
    return (_koHasValue & (1 << nr)) != 0;
}

void FunctionBlock::processInputKo(GroupObject &ko)
{
    auto index = FCB_KoCalcIndex(ko.asap());
    if (index >= FCB_KoCHKO0 && index <= FCB_KoCHKO8)
    {
        _koHasValue |= 1 << index;
        handleKo(ko);
    }
}

bool FunctionBlock::processCommand(const std::string cmd, bool diagnoseKo)
{
    return false;
}