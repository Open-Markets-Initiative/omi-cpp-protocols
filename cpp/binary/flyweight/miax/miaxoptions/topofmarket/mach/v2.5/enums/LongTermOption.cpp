#include "LongTermOption.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(LongTermOption value) {
    switch (value) {
        case LongTermOption::FarMonthExpiration: return "Far Month Expiration";
        case LongTermOption::NearMonthExpiration: return "Near Month Expiration";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LongTermOption value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
