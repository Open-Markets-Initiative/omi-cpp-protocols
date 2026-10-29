#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// Code identifying this message type
enum class MessageType : char {
    TimestampMessage = 'T',                  // Timestamp Message
    SystemEventMessage = 'S',                // System Event Message
    StockDirectoryMessage = 'R',             // Stock Directory Message
    StockTradingActionMessage = 'H',         // Stock Trading Action Message
    MarketParticipantPositionMessage = 'L',  // Market Participant Position Message
    AddOrderMessage = 'A',                   // Add Order Message
    AddOrderWithMpidMessage = 'F',           // Add Order With Mpid Message
    OrderExecutedMessage = 'E',              // Order Executed Message
    OrderExecutedWithPriceMessage = 'C',     // Order Executed With Price Message
    OrderCancelMessage = 'X',                // Order Cancel Message
    OrderDeleteMessage = 'D',                // Order Delete Message
    OrderReplaceMessage = 'U',               // Order Replace Message
    TradeMessage = 'P',                      // Trade Message
    CrossTradeMessage = 'Q',                 // Cross Trade Message
    BrokenTradeMessage = 'B',                // Broken Trade Message
    NetOrderImbalanceIndicatorMessage = 'I', // Net Order Imbalance Indicator Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
