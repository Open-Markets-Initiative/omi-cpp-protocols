#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',             // System Event Message
    OrderBookTradingActionMessage = 'H',  // Order Book Trading Action Message
    OrderBookDirectoryMessage = 'R',      // Order Book Directory Message
    AddOrderMessage = 'A',                // Add Order Message
    AddOrderMpidAttributionMessage = 'F', // Add Order Mpid Attribution Message
    OrderExecutedMessage = 'E',           // Order Executed Message
    OrderExecutedWithPriceMessage = 'C',  // Order Executed With Price Message
    OrderCancelMessage = 'X',             // Order Cancel Message
    OrderDeleteMessage = 'D',             // Order Delete Message
    OrderBookFlushMessage = 'Y',          // Order Book Flush Message
    OrderReplaceMessage = 'U',            // Order Replace Message
    TradeMessage = 'P',                   // Trade Message
    CrossTradeMessage = 'Q',              // Cross Trade Message
    BrokenTradeMessage = 'B',             // Broken Trade Message
    NoiiMessage = 'I',                    // Noii Message
    MoiiMessage = 'J',                    // Moii Message
    ExecutionSummaryMessage = 'K',        // Execution Summary Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
