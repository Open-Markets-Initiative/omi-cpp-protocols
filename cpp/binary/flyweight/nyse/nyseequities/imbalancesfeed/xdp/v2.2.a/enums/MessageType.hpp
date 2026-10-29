#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// The type of this message
enum class MessageType : std::uint16_t {
    SequenceNumberResetMessage = 1,        // Sequence Number Reset Message
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
    ImbalanceMessage = 105,                // Imbalance Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
