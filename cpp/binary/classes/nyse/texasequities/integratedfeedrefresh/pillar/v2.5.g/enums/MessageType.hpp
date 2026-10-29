#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

// The type of this message
enum class MessageType : std::uint16_t {
    SequenceNumberResetMessage = 1, // Sequence Number Reset Message
    SourceTimeReferenceMessage = 2, // Source Time Reference Message
    SymbolIndexMappingMessage = 3,  // Symbol Index Mapping Message
    SecurityStatusMessage = 34,     // Security Status Message
    RefreshHeaderMessage = 35,      // Refresh Header Message
    ImbalanceMessage = 105,         // Imbalance Message
    AddOrderRefreshMessage = 106,   // Add Order Refresh Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g
