#include "SesmPacketType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(SesmPacketType value) {
    switch (value) {
        case SesmPacketType::SequencedDataPacket: return "Sequenced Data Packet";
        case SesmPacketType::UnsequencedDataPacket: return "Unsequenced Data Packet";
        case SesmPacketType::LoginRequest: return "Login Request";
        case SesmPacketType::LoginResponse: return "Login Response";
        case SesmPacketType::SynchronizationComplete: return "Synchronization Complete";
        case SesmPacketType::RetransmissionRequest: return "Retransmission Request";
        case SesmPacketType::LogoutRequest: return "Logout Request";
        case SesmPacketType::GoodbyePacket: return "Goodbye Packet";
        case SesmPacketType::TradingSessionUpdate: return "Trading Session Update";
        case SesmPacketType::ServerHeartbeat: return "Server Heartbeat";
        case SesmPacketType::ClientHeartbeat: return "Client Heartbeat";
        case SesmPacketType::TestPacket: return "Test Packet";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SesmPacketType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
