#include "TradeCondition.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(TradeCondition value) {
    switch (value) {
        case TradeCondition::Matched: return "Matched";
        case TradeCondition::Legged: return "Legged";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
