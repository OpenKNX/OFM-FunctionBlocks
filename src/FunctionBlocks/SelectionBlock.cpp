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
    if (index >= FCB_KoCHKO0 && index <= FCB_KoCHKO7 && _currentIndex == index - FCB_KoCHKO0)
    {
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
    const uint8_t* sourceData = ko.valueRef();
    GroupObject& target = KoFCB_CHOutput;
    if (size == target.valueSize())
    {
        uint8_t* targetData = target.valueRef();
        memcpy(targetData, sourceData, size);
        target.objectWritten();
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
    if (max < 8 /* State can only exist if less then 8 inputs are defined */ && ParamFCB_CHSelectionStateOutput)
    {
        KoFCB_CHSelectionState.value(newIndex, dpt);
    }
    if (_currentIndex != newIndex)
    {
        _currentIndex = newIndex;
        // <Enumeration Text="Nichts senden" Value="0" Id="%ENID%" />
        // <Enumeration Text="Eingangswert senden oder Lesetelegram für Eingang wenn nicht gesetzt" Value="1" Id="%ENID%" />
        // <Enumeration Text="Eingangswert senden wenn bekannt, sonst 0-Wert" Value="2" Id="%ENID%" />		
        // <Enumeration Text="Eingangswert senden wenn bekannt, sonst nichts" Value="3" Id="%ENID%" />	
        auto behavior = ParamFCB_CHSelectionSwitching;						
	    if (behavior > 0)
        {
            auto goNr = FCB_KoCalcNumber(newIndex);
            GroupObject& ko = knx.getGroupObject(goNr);
            if (ko.initialized())
            {
                copyToOutput(ko);
            }
            else
            {
                switch (behavior)
                {
                    case 1:
                        ko.requestObjectRead();
                        break;
                    case 2:
                        GroupObject& target = KoFCB_CHOutput;
                        auto targetData = target.valueRef();
                        memset(targetData, 0, target.valueSize());
                        target.objectWritten();
                        break;
                }
            }   
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


