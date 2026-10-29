#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Code identifying message type
enum class MessageType : char {
    MarketEventMessage = 'A',        // Market Event Message
    SymbolInformationMessage = 'B',  // Symbol Information Message
    SymbolStateMessage = 'C',        // Symbol State Message
    NewOrderAddMessage = 'D',        // New Order Add Message
    OrderPartialCancelMessage = 'F', // Order Partial Cancel Message
    OrderCancelAllMessage = 'G',     // Order Cancel All Message
    OrderExecutedMessage = 'J',      // Order Executed Message
    TradeMessage = 'K',              // Trade Message
    TradeCancelMessage = 'L',        // Trade Cancel Message
    TradeCorrectMessage = 'M',       // Trade Correct Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
