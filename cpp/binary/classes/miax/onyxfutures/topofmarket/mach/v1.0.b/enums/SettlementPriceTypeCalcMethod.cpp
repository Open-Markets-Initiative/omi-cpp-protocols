#include "SettlementPriceTypeCalcMethod.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(SettlementPriceTypeCalcMethod value) {
    switch (value) {
        case SettlementPriceTypeCalcMethod::Actual: return "Actual";
        case SettlementPriceTypeCalcMethod::Theoretical: return "Theoretical";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlementPriceTypeCalcMethod value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
