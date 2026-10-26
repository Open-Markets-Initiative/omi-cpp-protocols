#pragma once

// Every flyweight view and reader of Iex.IexEquities.Tops.Snap.v1.6.

#include "structs/MessageHeader.hpp"
#include "messages/SnapshotRequestMessage.hpp"
#include "messages/ErrorResponseMessage.hpp"
#include "messages/SnapshotStartMessage.hpp"
#include "structs/IextpHeader.hpp"
#include "messages/SystemEventMessage.hpp"
#include "bitfields/SecurityDirectoryFlags.hpp"
#include "messages/SecurityDirectoryMessage.hpp"
#include "messages/TradingStatusMessage.hpp"
#include "messages/RetailLiquidityIndicatorMessage.hpp"
#include "messages/OperationalHaltStatusMessage.hpp"
#include "messages/ShortSalePriceTestStatusMessage.hpp"
#include "bitfields/QuoteUpdateFlags.hpp"
#include "messages/QuoteUpdateMessage.hpp"
#include "bitfields/SaleConditionFlags.hpp"
#include "messages/TradeReportMessage.hpp"
#include "messages/OfficialPriceMessage.hpp"
#include "messages/TradeBreakMessage.hpp"
#include "messages/AuctionInformationMessage.hpp"
#include "messages/SnapshotDataMessage.hpp"
#include "messages/SnapshotEndMessage.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"

#include "StreamReader.hpp"
