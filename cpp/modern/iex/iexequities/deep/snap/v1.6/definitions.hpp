#pragma once

#include "structs/MessageHeader.hpp"

#include "messages/SnapshotRequestMessage.hpp"
#include "messages/ErrorResponseMessage.hpp"
#include "messages/SnapshotStartMessage.hpp"
#include "messages/SnapshotDataMessage.hpp"
#include "messages/SystemEventMessage.hpp"
#include "messages/SecurityDirectoryMessage.hpp"
#include "messages/TradingStatusMessage.hpp"
#include "messages/RetailLiquidityIndicatorMessage.hpp"
#include "messages/OperationalHaltStatusMessage.hpp"
#include "messages/ShortSalePriceTestStatusMessage.hpp"
#include "messages/SecurityEventMessage.hpp"
#include "messages/PriceLevelBuyUpdateMessage.hpp"
#include "messages/PriceLevelSellUpdateMessage.hpp"
#include "messages/TradeReportMessage.hpp"
#include "messages/OfficialPriceMessage.hpp"
#include "messages/TradeBreakMessage.hpp"
#include "messages/AuctionInformationMessage.hpp"
#include "messages/SnapshotEndMessage.hpp"

#include "iterators/MessageIterator.hpp"
