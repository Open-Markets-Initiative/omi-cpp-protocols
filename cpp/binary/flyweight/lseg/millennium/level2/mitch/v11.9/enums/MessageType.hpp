#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// Code identifying this message type
enum class MessageType : std::uint8_t {
    TimeMessage = 84,                       // Time Message
    SystemEventMessage = 83,                // System Event Message
    SymbolDirectoryMessage = 82,            // Symbol Directory Message
    SymbolStatusMessage = 72,               // Symbol Status Message
    AddOrderMessage = 65,                   // Add Order Message
    AddAttributedOrderMessage = 70,         // Add Attributed Order Message
    OrderDeletedMessage = 68,               // Order Deleted Message
    OrderModifiedMessage = 85,              // Order Modified Message
    OrderBookClearMessage = 121,            // Order Book Clear Message
    OrderExecutedMessage = 69,              // Order Executed Message
    OrderExecutedWithPriceSizeMessage = 67, // Order Executed With Price Size Message
    TradeMessage = 80,                      // Trade Message
    AuctionTradeMessage = 81,               // Auction Trade Message
    AuctionInfoMessage = 73,                // Auction Info Message
    StatisticsMessage = 119,                // Statistics Message
    TopOfBookMessage = 113,                 // Top Of Book Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace lseg::millennium::level2::mitch::v11_9
