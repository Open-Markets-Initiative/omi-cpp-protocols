#include "EventCode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(EventCode value) {
    switch (value) {
        case EventCode::StartOfMessages: return "Start Of Messages";
        case EventCode::StartOfSystemHours: return "Start Of System Hours";
        case EventCode::StartOfMarketHours: return "Start Of Market Hours";
        case EventCode::EndOfMarketHours: return "End Of Market Hours";
        case EventCode::EndOfSystemHours: return "End Of System Hours";
        case EventCode::EndOfMessages: return "End Of Messages";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EventCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
