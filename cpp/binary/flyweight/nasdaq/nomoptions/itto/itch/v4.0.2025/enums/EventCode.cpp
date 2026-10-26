#include "EventCode.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(EventCode value) {
    switch (value) {
        case EventCode::StartOfMessages: return "Start Of Messages";
        case EventCode::StartOfSystemHours: return "Start Of System Hours";
        case EventCode::StartOfOpeningProcess: return "Start Of Opening Process";
        case EventCode::EndOfNormalHoursProcessing: return "End Of Normal Hours Processing";
        case EventCode::EndOfLateHoursProcessing: return "End Of Late Hours Processing";
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

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
