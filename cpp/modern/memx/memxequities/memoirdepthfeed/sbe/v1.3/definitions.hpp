#pragma once

#include "structs/CommonHeader.hpp"
#include "structs/SequencedMessage.hpp"
#include "structs/Message.hpp"
#include "structs/SbeHeader.hpp"

#include "messages/InstrumentDirectoryMessage.hpp"
#include "messages/RegShoRestrictionMessage.hpp"
#include "messages/SecurityTradingStatusMessage.hpp"
#include "messages/TradingSessionStatusMessage.hpp"
#include "messages/OrderAddedMessage.hpp"
#include "messages/OrderDeletedMessage.hpp"
#include "messages/OrderReducedMessage.hpp"
#include "messages/OrderExecutedMessage.hpp"
#include "messages/TradeMessage.hpp"
#include "messages/BrokenTradeMessage.hpp"
#include "messages/CorrectedTradeMessage.hpp"
#include "messages/ClearBookMessage.hpp"
#include "messages/SnapshotCompleteMessage.hpp"

#include "actions/Heartbeat.hpp"
#include "actions/SessionShutdown.hpp"

#include "iterators/MessageIterator.hpp"
