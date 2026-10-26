#pragma once

#include "structs/UnitHeader.hpp"
#include "structs/MessageHeader.hpp"

#include "messages/TimeMessage.hpp"
#include "messages/SystemEventMessage.hpp"
#include "messages/SymbolDirectoryMessage.hpp"
#include "messages/SymbolStatusMessage.hpp"
#include "messages/AddOrderMessage.hpp"
#include "messages/AddAttributedOrderMessage.hpp"
#include "messages/OrderDeletedMessage.hpp"
#include "messages/OrderModifiedMessage.hpp"
#include "messages/OrderBookClearMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/OrderExecutedWithPriceSizeMessage.hpp"
#include "messages/TradeMessage.hpp"
#include "messages/AuctionTradeMessage.hpp"
#include "messages/AuctionInfoMessage.hpp"
#include "messages/StatisticsMessage.hpp"
#include "messages/TopOfBookMessage.hpp"

#include "iterators/MessageIterator.hpp"
