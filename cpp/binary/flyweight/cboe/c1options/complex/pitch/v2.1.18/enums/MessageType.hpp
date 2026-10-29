#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Code identifying this message type
enum class MessageType : std::uint8_t {
    TimeMessage = 32,                                 // Time Message
    UnitClearMessage = 151,                           // Unit Clear Message
    TransactionBegin = 188,                           // Transaction Begin
    TransactionEndMessage = 189,                      // Transaction End Message
    ComplexInstrumentDefinitionExpandedMessage = 154, // Complex Instrument Definition Expanded Message
    SymbolMappingMessage = 46,                        // Symbol Mapping Message
    AddOrderLongMessage = 33,                         // Add Order Long Message
    AddOrderShortMessage = 34,                        // Add Order Short Message
    AddOrderExpandedMessage = 47,                     // Add Order Expanded Message
    OrderExecutedMessage = 35,                        // Order Executed Message
    OrderExecutedAtPriceSizeMessage = 36,             // Order Executed At Price Size Message
    ReduceSizeLongMessage = 37,                       // Reduce Size Long Message
    ReduceSizeShortMessage = 38,                      // Reduce Size Short Message
    ModifyOrderLongMessage = 39,                      // Modify Order Long Message
    ModifyOrderShortMessage = 40,                     // Modify Order Short Message
    DeleteOrderMessage = 41,                          // Delete Order Message
    TradeLongMessage = 42,                            // Trade Long Message
    TradeShortMessage = 43,                           // Trade Short Message
    AuctionNotificationMessage = 173,                 // Auction Notification Message
    AuctionCancelMessage = 174,                       // Auction Cancel Message
    AuctionTradeMessage = 175,                        // Auction Trade Message
    TradingStatusMessage = 49,                        // Trading Status Message
    AuctionUpdateMessage = 209,                       // Auction Update Message
    AuctionSummaryMessage = 150,                      // Auction Summary Message
    EndOfSessionMessage = 45,                         // End Of Session Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace cboe::c1options::complex::pitch::v2_1_18
