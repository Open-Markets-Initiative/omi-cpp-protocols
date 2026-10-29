#pragma once

#include "structs/MachPacketHeader.hpp"
#include "structs/ApplicationMessage.hpp"
#include "structs/CompactBid.hpp"
#include "structs/CompactOffer.hpp"
#include "structs/WideBid.hpp"
#include "structs/WideOffer.hpp"

#include "messages/SystemTimeMessage.hpp"
#include "messages/SeriesUpdate.hpp"
#include "messages/ComplexStrategyDefinitionMessage.hpp"
#include "messages/SystemStateMessage.hpp"
#include "messages/CompactComplexTopOfMarketBidMessage.hpp"
#include "messages/CompactComplexTopOfMarketOfferMessage.hpp"
#include "messages/WideComplexTopOfMarketBidMessage.hpp"
#include "messages/WideComplexTopOfMarketOfferMessage.hpp"
#include "messages/CompactComplexDoubleSidedTopOfMarketMessage.hpp"
#include "messages/WideComplexDoubleSidedTopOfMarketMessage.hpp"
#include "messages/StrategyTradeMessage.hpp"
#include "messages/UnderlyingTradingStatusMessage.hpp"

#include "iterators/LegDefinitionIterator.hpp"
#include "iterators/MachMessageIterator.hpp"
