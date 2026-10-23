#include "EventCode.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

std::string_view to_string(EventCode value) {
    switch (value) {
        case EventCode::StartOfMessages: return "Start Of Messages";
        case EventCode::StartOfSystemHours: return "Start Of System Hours";
        case EventCode::StartOfOpeningProcess: return "Start Of Opening Process";
        case EventCode::StartOfNormalHoursClosingProcess: return "Start Of Normal Hours Closing Process";
        case EventCode::StartOfLateHoursClosingProcess: return "Start Of Late Hours Closing Process";
        case EventCode::EndOfSystemHours: return "End Of System Hours";
        case EventCode::EndOfMessages: return "End Of Messages";
        case EventCode::EndOfWcoEarlyClosing: return "End Of Wco Early Closing";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EventCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
