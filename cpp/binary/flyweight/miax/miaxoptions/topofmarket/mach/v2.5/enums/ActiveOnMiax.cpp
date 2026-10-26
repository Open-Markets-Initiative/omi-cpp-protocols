#include "ActiveOnMiax.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(ActiveOnMiax value) {
    switch (value) {
        case ActiveOnMiax::Active: return "Active";
        case ActiveOnMiax::Inactive: return "Inactive";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ActiveOnMiax value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
