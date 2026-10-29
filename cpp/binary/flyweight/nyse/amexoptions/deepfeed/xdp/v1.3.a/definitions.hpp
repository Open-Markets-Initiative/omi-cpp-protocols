#pragma once

// Every flyweight view and reader of Nyse.AmexOptions.DeepFeed.Xdp.v1.3.a.

#include "structs/SendTime.hpp"
#include "structs/PacketHeader.hpp"
#include "structs/MessageHeader.hpp"
#include "messages/OutrightMarketDepthBuyMessage.hpp"
#include "messages/OutrightMarketDepthSellMessage.hpp"
#include "messages/UnderlyingStatusMessage.hpp"
#include "messages/OutrightSeriesStatusMessage.hpp"
#include "messages/RefreshOutrightMarketDepthBuyMessage.hpp"
#include "messages/RefreshOutrightMarketDepthSellMessage.hpp"
#include "messages/UnderlyingIndexMappingMessage.hpp"
#include "messages/SeriesIndexMappingMessage.hpp"
#include "messages/StreamIdMessage.hpp"
#include "messages/SequenceNumberResetMessage.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"

#include "PacketReader.hpp"
