#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// A flag that indicates whether this is an original, retransmitted, or ‘replayed’ message.
enum class DeliveryFlag : std::uint8_t {
    Heartbeat = 1,                      // Heartbeat
    ContainsOriginalAndRefreshMsgs = 2, // Contains Original And Refresh Msgs
    ContainsOnlyRefreshMessages = 3,    // Contains Only Refresh Messages
    XdpFailover = 10,                   // XDP Failover
    ContainsOnlyOriginalMessages = 11,  // Contains Only Original Messages
    SequenceNumberResetMessage = 12,    // Sequence Number Reset Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(DeliveryFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, DeliveryFlag value);

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
