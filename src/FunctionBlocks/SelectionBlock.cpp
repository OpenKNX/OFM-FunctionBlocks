#include "SelectionBlock.h"

#define KoFCB_CHSelectionState KoFCB_CHKO7

#define KoFCB_CHSelection KoFCB_CHKO8
#define FCB_KoCHSelection FCB_KoCHKO8

#define KoFCB_CHOutput KoFCB_CHKO9

SelectionBlock::SelectionBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "Selection")
{
    setNewIndex(0);  
}

void SelectionBlock::handleKo(GroupObject &ko)
{
    auto index = FCB_KoCalcIndex(ko.asap());
    if (index >= FCB_KoCHKO0 && index <= FCB_KoCHKO7)
    {
        auto input = index - FCB_KoCHKO0;
        if (_currentIndex == input)
           copyToOutput(ko);
    }
    else if (index == FCB_KoCHSelection)
    {
        uint8_t newIndex = ko.value(DPT_Value_1_Ucount);
        setNewIndex(newIndex);  
    }
}

void SelectionBlock::copyToOutput(GroupObject &ko)
{
    size_t size = ko.valueSize();
    uint8_t* sourceData = ko.valueRef();
    GroupObject& target = KoFCB_CHOutput;
    if (size == target.valueSize())
    {
        uint8_t* targetData = target.valueRef();
        memcpy(sourceData, targetData, size);
    }
}

void SelectionBlock::setNewIndex(uint8_t newIndex)
{
     // <Enumeration Text="   2-fach Auswahl" Value="2" Id="%ENID%" />
    // <Enumeration Text="2x 2-fach Auswahl" Value="22" Id="%ENID%" />
    // <Enumeration Text="3x 2-fach Auswahl (kein Statusausgang möglich)" Value="32" Id="%ENID%" />
    Dpt dpt;
    uint8_t max;
    switch (ParamFCB_CHSelectionType)
    {
        case 2:
        case 22:
        case 32:
            max = 2;
            dpt = DPT_Switch;
            break;
        default:
            max = ParamFCB_CHSelectionType;
            dpt = DPT_Value_1_Ucount;
    }
    if (newIndex > max)
    {
        return;
    }
    if (max < 8 && ParamFCB_CHSelectionStateOutput)
    {
        KoFCB_CHSelectionState.value(newIndex, dpt);
    }
    if (_currentIndex != newIndex)
    {
        _currentIndex = newIndex;
        // <Enumeration Text="Nichts senden" Value="0" Id="%ENID%" />
        // <Enumeration Text="Eingangswert senden" Value="1" Id="%ENID%" />
        if ((bool)ParamFCB_CHSelectionSwitching)
        {
            GroupObject& ko = knx.getGroupObject(FCB_KoCalcNumber(newIndex));
            if (ko.initialized())
                copyToOutput(ko);
        }
    }
}

void SelectionBlock::readInputKos()
{
    if (!KoFCB_CHSelection.initialized())
    {
        KoFCB_CHSelection.requestObjectRead();
    }
}

void SelectionBlock::initMissingInputValues()
{
}


