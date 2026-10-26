#include "MachPacketType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(MachPacketType value) {
    switch (value) {
        case MachPacketType::Heartbeat: return "Heartbeat";
        case MachPacketType::StartOfSession: return "Start Of Session";
        case MachPacketType::EndOfSession: return "End Of Session";
        case MachPacketType::ApplicationMessage: return "Application Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MachPacketType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
