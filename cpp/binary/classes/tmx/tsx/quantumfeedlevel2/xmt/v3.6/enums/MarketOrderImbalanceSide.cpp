// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/MarketOrderImbalanceSide.cpp
#include "MarketOrderImbalanceSide.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(MarketOrderImbalanceSide value) {
    switch (value) {
        case MarketOrderImbalanceSide::Buy: return "Buy";
        case MarketOrderImbalanceSide::Sell: return "Sell";
        case MarketOrderImbalanceSide::NoImbalanceExists: return "No Imbalance Exists";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketOrderImbalanceSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
