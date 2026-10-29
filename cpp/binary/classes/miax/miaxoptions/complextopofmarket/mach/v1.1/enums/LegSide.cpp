#include "LegSide.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::Bid: return "Bid";
        case LegSide::Ask: return "Ask";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
