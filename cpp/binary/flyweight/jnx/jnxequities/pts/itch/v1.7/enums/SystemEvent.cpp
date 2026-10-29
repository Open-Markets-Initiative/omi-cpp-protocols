#include "SystemEvent.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

std::string_view to_string(SystemEvent value) {
    switch (value) {
        case SystemEvent::StartOfMessages: return "Start Of Messages";
        case SystemEvent::StartOfSystemHours: return "Start Of System Hours";
        case SystemEvent::StartOfMarketHours: return "Start Of Market Hours";
        case SystemEvent::EndOfMarketHours: return "End Of Market Hours";
        case SystemEvent::EndOfSystemHours: return "End Of System Hours";
        case SystemEvent::EndOfMessages: return "End Of Messages";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SystemEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::itch::v1_7
