#pragma once

// Every flyweight view and reader of Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1.

#include "structs/MachPacketHeader.hpp"
#include "messages/SystemTimeMessage.hpp"
#include "messages/SeriesUpdate.hpp"
#include "groups/LegDefinition.hpp"
#include "messages/ComplexStrategyDefinitionMessage.hpp"
#include "messages/SystemStateMessage.hpp"
#include "messages/CompactComplexTopOfMarketBidMessage.hpp"
#include "messages/CompactComplexTopOfMarketOfferMessage.hpp"
#include "messages/WideComplexTopOfMarketBidMessage.hpp"
#include "messages/WideComplexTopOfMarketOfferMessage.hpp"
#include "structs/CompactBid.hpp"
#include "structs/CompactOffer.hpp"
#include "messages/CompactComplexDoubleSidedTopOfMarketMessage.hpp"
#include "structs/WideBid.hpp"
#include "structs/WideOffer.hpp"
#include "messages/WideComplexDoubleSidedTopOfMarketMessage.hpp"
#include "messages/StrategyTradeMessage.hpp"
#include "messages/UnderlyingTradingStatusMessage.hpp"
#include "messages/ApplicationMessage.hpp"
#include "structs/Packet.hpp"
#include "structs/Frame.hpp"

#include "PacketReader.hpp"
