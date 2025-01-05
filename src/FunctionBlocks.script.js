// OFM-FunctionBlocks --
// SPDX-License-Identifier: AGPL-3.0-only

function fcbAddChannel(device, online, progress, context) {
    var numberOfChannelds = device.getParameterByName('FCB_VisibleChannels');
    var newNumberOfChannels = numberOfChannelds.value + 1;
    var channelType = device.getParameterByName('FCB_CH' + newNumberOfChannels + 'ChannelType');
    var notAllowed = device.getParameterByName('FCB_AddNotAllowed');
    if (channelType == 0)
    {
        notAllowed.value = 1;
    }
    else
    {
        notAllowed.value = 0;
        numberOfChannelds.value = numberOfChannelds.value + 1;
    }
}

// -- OFM-FunctionBlocks //
