#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// The type of this message
enum class MessageType : std::uint16_t {
    SequenceNumberResetMessage = 1,                // Sequence Number Reset Message
    SourceTimeReferenceMessage = 2,                // Source Time Reference Message
    SymbolIndexMappingMessage = 3,                 // Symbol Index Mapping Message
    SymbolClearMessage = 32,                       // Symbol Clear Message
    SecurityStatusMessage = 34,                    // Security Status Message
    RetransmissionRequestMessage = 10,             // Retransmission Request Message
    SymbolIndexMappingRequestMessage = 13,         // Symbol Index Mapping Request Message
    RefreshRequestMessage = 15,                    // Refresh Request Message
    MessageUnavailableMessage = 31,                // Message Unavailable Message
    RefreshHeaderMessage = 35,                     // Refresh Header Message
    RequestResponseMessage = 11,                   // Request Response Message
    HeartbeatResponseMessage = 12,                 // Heartbeat Response Message
    TradeMessage = 220,                            // Trade Message
    TradeCancelMessage = 221,                      // Trade Cancel Message
    TradeCorrectionMessage = 222,                  // Trade Correction Message
    StockSummaryMessage = 223,                     // Stock Summary Message
    TrfFractionalTradeMessage = 210,               // Trf Fractional Trade Message
    TrfTradeCancelMessage = 216,                   // Trf Trade Cancel Message
    TrfFractionalTradeCorrectionMessage = 212,     // Trf Fractional Trade Correction Message
    TrfFractionalPriorDayTradeMessage = 213,       // Trf Fractional Prior Day Trade Message
    TrfFractionalPriorDayTradeCancelMessage = 214, // Trf Fractional Prior Day Trade Cancel Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::nationalequities::trades::pillar::v2_6
