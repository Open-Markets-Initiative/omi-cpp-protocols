#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// The type of this message
enum class MessageType : std::uint16_t {
    SequenceNumberResetMessage = 1,      // Sequence Number Reset Message
    SourceTimeReferenceMessage = 2,      // Source Time Reference Message
    SymbolIndexMappingMessage = 3,       // Symbol Index Mapping Message
    SymbolClearMessage = 32,             // Symbol Clear Message
    SecurityStatusMessage = 34,          // Security Status Message
    AddOrderMessage = 100,               // Add Order Message
    ModifyOrderMessage = 101,            // Modify Order Message
    DeleteOrderMessage = 102,            // Delete Order Message
    OrderExecutionMessage = 103,         // Order Execution Message
    ReplaceOrderMessage = 104,           // Replace Order Message
    ImbalanceMessage = 105,              // Imbalance Message
    AddOrderRefreshMessage = 106,        // Add Order Refresh Message
    NonDisplayedTradeMessage = 110,      // Non Displayed Trade Message
    CrossTradeMessage = 111,             // Cross Trade Message
    TradeCancelMessage = 112,            // Trade Cancel Message
    CrossCorrectionMessage = 113,        // Cross Correction Message
    RetailPriceImprovementMessage = 114, // Retail Price Improvement Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g
