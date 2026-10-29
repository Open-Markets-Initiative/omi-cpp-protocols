#include "PacketType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(PacketType value) {
    switch (value) {
        case PacketType::Heartbeat: return "Heartbeat";
        case PacketType::StartOfSession: return "Start Of Session";
        case PacketType::EndOfSession: return "End Of Session";
        case PacketType::ApplicationMessage: return "Application Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PacketType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
