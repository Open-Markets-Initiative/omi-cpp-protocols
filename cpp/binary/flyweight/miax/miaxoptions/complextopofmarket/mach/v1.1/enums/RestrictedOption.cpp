#include "RestrictedOption.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(RestrictedOption value) {
    switch (value) {
        case RestrictedOption::Yes: return "Yes";
        case RestrictedOption::No: return "No";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RestrictedOption value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
