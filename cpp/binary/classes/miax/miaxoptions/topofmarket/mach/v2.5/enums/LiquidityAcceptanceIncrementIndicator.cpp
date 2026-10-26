#include "LiquidityAcceptanceIncrementIndicator.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(LiquidityAcceptanceIncrementIndicator value) {
    switch (value) {
        case LiquidityAcceptanceIncrementIndicator::Penny: return "Penny";
        case LiquidityAcceptanceIncrementIndicator::PennyOrNickel: return "Penny Or Nickel";
        case LiquidityAcceptanceIncrementIndicator::NickelOrDime: return "Nickel Or Dime";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LiquidityAcceptanceIncrementIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
