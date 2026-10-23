#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

// Code identifying this message type
enum class MessageType : std::uint8_t {
    TimeMessage = 32,                     // Time Message
    UnitClearMessage = 151,               // Unit Clear Message
    AddOrderLongMessage = 33,             // Add Order Long Message
    AddOrderShortMessage = 34,            // Add Order Short Message
    AddOrderExpandedMessage = 47,         // Add Order Expanded Message
    OrderExecutedMessage = 35,            // Order Executed Message
    OrderExecutedAtPriceSizeMessage = 36, // Order Executed At Price Size Message
    ReduceSizeLongMessage = 37,           // Reduce Size Long Message
    ReduceSizeShortMessage = 38,          // Reduce Size Short Message
    ModifyOrderLongMessage = 39,          // Modify Order Long Message
    ModifyOrderShortMessage = 40,         // Modify Order Short Message
    DeleteOrderMessage = 41,              // Delete Order Message
    TradeLongMessage = 42,                // Trade Long Message
    TradeShortMessage = 43,               // Trade Short Message
    TradeExpandedMessage = 48,            // Trade Expanded Message
    TradeBreakMessage = 44,               // Trade Break Message
    EndOfSession = 45,                    // End Of Session
    TradingStatusMessage = 49,            // Trading Status Message
    AuctionUpdateMessage = 149,           // Auction Update Message
    AuctionSummaryMessage = 150,          // Auction Summary Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29
