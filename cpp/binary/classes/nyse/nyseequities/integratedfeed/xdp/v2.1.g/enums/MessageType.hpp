#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// The type of this message
enum class MessageType : std::uint16_t {
    SequenceNumberResetMessage = 1,        // Sequence Number Reset Message
    SourceTimeReferenceMessage = 2,        // Source Time Reference Message
    SymbolIndexMappingMessage = 3,         // Symbol Index Mapping Message
    RetransmissionRequestMessage = 10,     // Retransmission Request Message
    RequestResponseMessage = 11,           // Request Response Message
    HeartbeatResponseMessage = 12,         // Heartbeat Response Message
    SymbolIndexMappingRequestMessage = 13, // Symbol Index Mapping Request Message
    RefreshRequestMessage = 15,            // Refresh Request Message
    MessageUnavailableMessage = 31,        // Message Unavailable Message
    SymbolClearMessage = 32,               // Symbol Clear Message
    SecurityStatusMessage = 34,            // Security Status Message
    RefreshHeaderMessage = 35,             // Refresh Header Message
    AddOrderMessage = 100,                 // Add Order Message
    ModifyOrderMessage = 101,              // Modify Order Message
    ReplaceOrderMessage = 104,             // Replace Order Message
    DeleteOrderMessage = 102,              // Delete Order Message
    TradeCancelMessage = 112,              // Trade Cancel Message
    CrossTradeMessage = 111,               // Cross Trade Message
    CrossCorrectionMessage = 113,          // Cross Correction Message
    RetailPriceImprovementMessage = 114,   // Retail Price Improvement Message
    AddOrderRefreshMessage = 106,          // Add Order Refresh Message
    ImbalanceMessage = 105,                // Imbalance Message
    OrderExecutionMessage = 103,           // Order Execution Message
    NonDisplayedTradeMessage = 110,        // Non Displayed Trade Message
    StockSummaryMessage = 223,             // Stock Summary Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
