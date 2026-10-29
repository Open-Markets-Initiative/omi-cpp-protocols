#include "SettlementCurrency.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(SettlementCurrency value) {
    switch (value) {
        case SettlementCurrency::Usd: return "Usd";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlementCurrency value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
