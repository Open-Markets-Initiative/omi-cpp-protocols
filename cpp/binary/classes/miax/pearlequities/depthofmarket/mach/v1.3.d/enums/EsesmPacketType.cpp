#include "EsesmPacketType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(EsesmPacketType value) {
    switch (value) {
        case EsesmPacketType::SequencedDataPacket: return "Sequenced Data Packet";
        case EsesmPacketType::UnsequencedDataPacket: return "Unsequenced Data Packet";
        case EsesmPacketType::LoginRequest: return "Login Request";
        case EsesmPacketType::LoginResponse: return "Login Response";
        case EsesmPacketType::SynchronizationComplete: return "Synchronization Complete";
        case EsesmPacketType::RetransmissionRequest: return "Retransmission Request";
        case EsesmPacketType::LogoutRequest: return "Logout Request";
        case EsesmPacketType::GoodbyePacket: return "Goodbye Packet";
        case EsesmPacketType::TradingSessionUpdate: return "Trading Session Update";
        case EsesmPacketType::ServerHeartbeat: return "Server Heartbeat";
        case EsesmPacketType::ClientHeartbeat: return "Client Heartbeat";
        case EsesmPacketType::TestPacket: return "Test Packet";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EsesmPacketType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
