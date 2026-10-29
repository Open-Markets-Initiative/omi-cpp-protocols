#include "LiquidityAcceptanceIncrementIndicator.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::string_view to_string(LiquidityAcceptanceIncrementIndicator value) {
    switch (value) {
        case LiquidityAcceptanceIncrementIndicator::Penny: return "Penny";
        case LiquidityAcceptanceIncrementIndicator::Nickel: return "Nickel";
        case LiquidityAcceptanceIncrementIndicator::Dime: return "Dime";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LiquidityAcceptanceIncrementIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
