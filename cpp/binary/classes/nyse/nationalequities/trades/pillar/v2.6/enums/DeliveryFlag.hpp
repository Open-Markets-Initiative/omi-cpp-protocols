#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// A flag that indicates whether this is an original, retransmitted, or ‘replayed’ message
enum class DeliveryFlag : std::uint8_t {
    Heartbeat = 1,                      // Heartbeat
    PillarFailover = 10,                // Pillar Failover
    OriginalMessage = 11,               // Original Message
    SequenceNumberResetMessage = 12,    // Sequence Number Reset Message
    OneRetransmissionPacket = 13,       // One Retransmission Packet
    RetransmissionSequenceMessage = 15, // Retransmission Sequence Message
    OneRefreshPacket = 17,              // One Refresh Packet
    RefreshSequenceStart = 18,          // Refresh Sequence Start
    RefreshSequenceMessage = 19,        // Refresh Sequence Message
    RefreshSequenceEnd = 20,            // Refresh Sequence End
    MessageUnavailable = 21,            // Message Unavailable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(DeliveryFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, DeliveryFlag value);

} // namespace nyse::nationalequities::trades::pillar::v2_6
