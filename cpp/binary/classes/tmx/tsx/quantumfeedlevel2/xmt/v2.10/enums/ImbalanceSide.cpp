// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/ImbalanceSide.cpp
#include "ImbalanceSide.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(ImbalanceSide value) {
    switch (value) {
        case ImbalanceSide::Buy: return "Buy";
        case ImbalanceSide::Sell: return "Sell";
        case ImbalanceSide::NoImbalanceExists: return "No Imbalance Exists";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
