#include "EventReason.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

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

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
