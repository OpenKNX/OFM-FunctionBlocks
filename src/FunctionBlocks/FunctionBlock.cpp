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

Dpt FunctionBlock::dptType(uint8_t typeParamValue)
{
    // <Enumeration Text="1.*           1-Bit (0/1)"                      Value="10"   Id="%ENID%" />								
    // <Enumeration Text="5.*           8-Bit vorzeichenlos"              Value="50"   Id="%ENID%" />
    // <Enumeration Text="5.001       Prozent (0..100%)"                  Value="51"   Id="%ENID%" />
    // <Enumeration Text="6.*           8-Bit vorzeichenbehaftet"         Value="61"   Id="%ENID%" />
    // <Enumeration Text="7.*           2-Byte vorzeichenlos"             Value="70"   Id="%ENID%" />
    // <Enumeration Text="8.*           2-Byte vorzeichenbehaftet"        Value="80"   Id="%ENID%" />
    // <Enumeration Text="9.*           2-Byte Gleitkommawert"            Value="90"   Id="%ENID%" />
    // <Enumeration Text="12.*         4-Byte vorzeichenlos"             Value="120"   Id="%ENID%" />
    // <Enumeration Text="13.*         4-Byte vorzeichenbehaftet"        Value="130"   Id="%ENID%" />
    // <Enumeration Text="14.*         4-Byte Gleitkommawert"            Value="140"   Id="%ENID%" />
    Dpt dptInput;
    switch (typeParamValue)
    {
        case 10:
            dptInput = DPT_Switch;
            break;
        case 50:
            dptInput = DPT_Value_1_Ucount;
            break;
        case 51:
            dptInput = DPT_Scaling;
            break;
        case 61:
            dptInput = DPT_Value_1_Count;
            break;
        case 70:
            dptInput = DPT_Value_2_Ucount;
            break;
        case 80:
            dptInput = DPT_Value_2_Count;
            break;
        case 90:
            dptInput = DPT_Value_Temp;
            break;
        case 120:
            dptInput = DPT_Value_4_Ucount;
            break;
        case 130:
            dptInput = DPT_Value_4_Count;
            break;
        case 140:
            dptInput = DPT_Value_Amplitude;
            break;
        default:
            dptInput = DPT_Switch;
            break;
    }
    return dptInput;
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