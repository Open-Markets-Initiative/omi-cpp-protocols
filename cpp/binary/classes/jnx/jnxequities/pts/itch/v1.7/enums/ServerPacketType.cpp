#include "ServerPacketType.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

std::string_view to_string(ServerPacketType value) {
    switch (value) {
        case ServerPacketType::DebugPacket: return "Debug Packet";
        case ServerPacketType::LoginAcceptedPacket: return "Login Accepted Packet";
        case ServerPacketType::LoginRejectedPacket: return "Login Rejected Packet";
        case ServerPacketType::SequencedDataPacket: return "Sequenced Data Packet";
        case ServerPacketType::ServerHeartbeatPacket: return "Server Heartbeat Packet";
        case ServerPacketType::EndOfSessionPacket: return "End Of Session Packet";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ServerPacketType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::itch::v1_7
