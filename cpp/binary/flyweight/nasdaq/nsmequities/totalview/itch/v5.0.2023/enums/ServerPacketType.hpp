#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Code identifying this packet type sent by the server
enum class ServerPacketType : char {
    DebugPacket = '+',           // Debug Packet
    LoginAcceptedPacket = 'A',   // Login Accepted Packet
    LoginRejectedPacket = 'J',   // Login Rejected Packet
    SequencedDataPacket = 'S',   // Sequenced Data Packet
    ServerHeartbeatPacket = 'H', // Server Heartbeat Packet
    EndOfSessionPacket = 'Z',    // End Of Session Packet
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ServerPacketType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ServerPacketType value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
