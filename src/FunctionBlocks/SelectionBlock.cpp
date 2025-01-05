#include "SelectionBlock.h"

#define KoFCB_CHSelectionState KoFCB_CHKO7
#define KoFCB_CHSelection KoFCB_CHKO8
#define KoFCB_CHOutput KoFCB_CHKO9

SelectionBlock::SelectionBlock(uint8_t channelIndex)
    : FunctionBlock(channelIndex, "Selection")
{
    
}

void SelectionBlock::handleKo(GroupObject &ko)
{
    
}

void SelectionBlock::readInputKos()
{
}

void SelectionBlock::initMissingInputValues()
{
}


