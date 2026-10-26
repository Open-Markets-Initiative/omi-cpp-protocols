#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The type of this message
enum class MessageType : std::uint16_t {
    SequenceNumberResetMessage = 1,            // Sequence Number Reset Message
    SourceTimeReferenceMessage = 2,            // Source Time Reference Message
    SymbolIndexMappingMessage = 3,             // Symbol Index Mapping Message
    SymbolClearMessage = 32,                   // Symbol Clear Message
    SecurityStatusMessage = 34,                // Security Status Message
    OutrightSeriesIndexMappingMessage = 50,    // Outright Series Index Mapping Message
    OptionsStatusMessage = 51,                 // Options Status Message
    ComplexSeriesIndexMappingMessage = 60,     // Complex Series Index Mapping Message
    RetransmissionRequestMessage = 10,         // Retransmission Request Message
    RefreshHeaderMessage = 35,                 // Refresh Header Message
    RefreshRequestMessage = 15,                // Refresh Request Message
    SymbolIndexMappingRequestMessage = 13,     // Symbol Index Mapping Request Message
    MessageUnavailableMessage = 31,            // Message Unavailable Message
    RequestResponseMessage = 11,               // Request Response Message
    HeartbeatResponseMessage = 12,             // Heartbeat Response Message
    OptionsAddOrderMessage = 300,              // Options Add Order Message
    OptionsModifyOrderMessage = 301,           // Options Modify Order Message
    OptionsDeleteOrderMessage = 302,           // Options Delete Order Message
    OptionsOrderExecutionMessage = 303,        // Options Order Execution Message
    OptionsReplaceOrderMessage = 304,          // Options Replace Order Message
    OptionsImbalanceMessage = 305,             // Options Imbalance Message
    OptionsAddOrderRefreshMessage = 306,       // Options Add Order Refresh Message
    OptionsSeriesRfqMessage = 307,             // Options Series Rfq Message
    OptionsNonDisplayedTradeMessage = 310,     // Options Non Displayed Trade Message
    OptionsCrossTradeMessage = 311,            // Options Cross Trade Message
    OptionsTradeCancelMessage = 312,           // Options Trade Cancel Message
    OptionsOutrightSeriesSummaryMessage = 323, // Options Outright Series Summary Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
