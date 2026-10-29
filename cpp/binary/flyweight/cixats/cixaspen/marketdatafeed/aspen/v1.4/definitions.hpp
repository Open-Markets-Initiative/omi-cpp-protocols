#pragma once

// Every flyweight view and reader of CixAts.CixAspen.MarketDataFeed.Aspen.v1.4.

#include "structs/PacketHeader.hpp"
#include "structs/MessageHeader.hpp"
#include "messages/MarketEventMessage.hpp"
#include "messages/SymbolInformationMessage.hpp"
#include "messages/SymbolStateMessage.hpp"
#include "messages/NewOrderAddMessage.hpp"
#include "messages/OrderPartialCancelMessage.hpp"
#include "messages/OrderCancelAllMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/TradeMessage.hpp"
#include "messages/TradeCancelMessage.hpp"
#include "messages/TradeCorrectMessage.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"

#include "PacketReader.hpp"
