#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The type of this message
enum class MessageType : std::uint16_t {
    SequenceNumberResetMessage = 1,         // Sequence Number Reset Message
    TimeReferenceMessage = 2,               // Time Reference Message
    SymbolIndexMappingMessage = 3,          // Symbol Index Mapping Message
    RetransmissionRequestMessage = 10,      // Retransmission Request Message
    RequestResponseMessage = 11,            // Request Response Message
    HeartbeatResponseMessage = 12,          // Heartbeat Response Message
    SymbolIndexMappingRequestMessage = 13,  // Symbol Index Mapping Request Message
    RefreshRequestMessage = 15,             // Refresh Request Message
    MessageUnavailableMessage = 31,         // Message Unavailable Message
    SymbolClearMessage = 32,                // Symbol Clear Message
    SecurityStatusMessage = 34,             // Security Status Message
    RefreshHeaderMessage = 35,              // Refresh Header Message
    OutrightSeriesIndexMappingMessage = 50, // Outright Series Index Mapping Message
    OptionsStatusMessage = 51,              // Options Status Message
    OptionsQuoteMessage = 340,              // Options Quote Message
    OptionsTradeMessage = 320,              // Options Trade Message
    OptionsTradeCancelMessage = 321,        // Options Trade Cancel Message
    OptionsTradeCorrectionMessage = 322,    // Options Trade Correction Message
    OptionsImbalanceMessage = 305,          // Options Imbalance Message
    SeriesRfqMessage = 307,                 // Series Rfq Message
    OutrightSeriesSummaryMessage = 323,     // Outright Series Summary Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
