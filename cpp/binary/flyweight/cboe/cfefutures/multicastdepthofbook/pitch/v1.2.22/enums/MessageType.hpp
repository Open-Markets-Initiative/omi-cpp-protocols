#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Code identifying this message type
enum class MessageType : std::uint8_t {
    TimeReferenceMessage = 177,                // Time Reference Message
    TimeMessage = 32,                          // Time Message
    UnitClearMessage = 151,                    // Unit Clear Message
    FuturesInstrumentDefinitionMessage = 187,  // Futures Instrument Definition Message
    FuturesVarianceSymbolMappingMessage = 250, // Futures Variance Symbol Mapping Message
    PriceLimitsMessage = 190,                  // Price Limits Message
    AddOrderLongMessage = 33,                  // Add Order Long Message
    AddOrderShortMessage = 34,                 // Add Order Short Message
    OrderExecutedMessage = 35,                 // Order Executed Message
    ReduceSizeLongMessage = 37,                // Reduce Size Long Message
    ReduceSizeShortMessage = 38,               // Reduce Size Short Message
    ModifyOrderLongMessage = 39,               // Modify Order Long Message
    ModifyOrderShortMessage = 40,              // Modify Order Short Message
    DeleteOrderMessage = 41,                   // Delete Order Message
    TradeLongMessage = 42,                     // Trade Long Message
    TradeShortMessage = 43,                    // Trade Short Message
    TransactionBeginMessage = 188,             // Transaction Begin Message
    TransactionEndMessage = 189,               // Transaction End Message
    TradeBreakMessage = 44,                    // Trade Break Message
    SettlementMessage = 185,                   // Settlement Message
    OpenInterestMessage = 211,                 // Open Interest Message
    EndOfDaySummaryMessage = 186,              // End Of Day Summary Message
    TradingStatusMessage = 49,                 // Trading Status Message
    EndOfSessionMessage = 45,                  // End Of Session Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
