#include "RestrictedOption.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(RestrictedOption value) {
    switch (value) {
        case RestrictedOption::AcceptPositionClosing: return "Accept Position Closing";
        case RestrictedOption::AcceptOpenAndClose: return "Accept Open And Close";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RestrictedOption value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
