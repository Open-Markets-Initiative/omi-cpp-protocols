#include "ClientPacketType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(ClientPacketType value) {
    switch (value) {
        case ClientPacketType::DebugPacket: return "Debug Packet";
        case ClientPacketType::LoginRequestPacket: return "Login Request Packet";
        case ClientPacketType::UnsequencedDataPacket: return "Unsequenced Data Packet";
        case ClientPacketType::ClientHeartbeatPacket: return "Client Heartbeat Packet";
        case ClientPacketType::LogoutRequestPacket: return "Logout Request Packet";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ClientPacketType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
