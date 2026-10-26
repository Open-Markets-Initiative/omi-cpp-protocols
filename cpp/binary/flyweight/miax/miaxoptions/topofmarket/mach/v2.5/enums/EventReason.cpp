#include "EventReason.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(EventReason value) {
    switch (value) {
        case EventReason::Automatic: return "Automatic";
        case EventReason::Manual: return "Manual";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EventReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
