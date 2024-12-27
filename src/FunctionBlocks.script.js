// OFM-FunctionBlocks --
// SPDX-License-Identifier: AGPL-3.0-only

function fcbAddChannel(device, online, progress, context) {
    var numberOfChannelds = device.getParameterByName('FCB_VisibleChannels');
    numberOfChannelds.value = numberOfChannelds.value + 1;
}

// -- OFM-FunctionBlocks //
