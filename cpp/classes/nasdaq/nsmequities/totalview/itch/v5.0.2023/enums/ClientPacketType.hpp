#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Code identifying this packet type sent by the client
enum class ClientPacketType : char {
    DebugPacket = '+',           // Debug Packet
    LoginRequestPacket = 'L',    // Login Request Packet
    UnsequencedDataPacket = 'U', // Unsequenced Data Packet
    ClientHeartbeatPacket = 'R', // Client Heartbeat Packet
    LogoutRequestPacket = 'O',   // Logout Request Packet
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ClientPacketType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ClientPacketType value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
