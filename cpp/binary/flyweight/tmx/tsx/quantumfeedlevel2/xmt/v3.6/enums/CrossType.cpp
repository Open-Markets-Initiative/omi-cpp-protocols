// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/CrossType.cpp
#include "CrossType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::Internal: return "Internal";
        case CrossType::Basis: return "Basis";
        case CrossType::Contingent: return "Contingent";
        case CrossType::DerivativeRelated: return "Derivative Related";
        case CrossType::Regular: return "Regular";
        case CrossType::SpecialTradingSession: return "Special Trading Session";
        case CrossType::VolumeWeightedAveragePrice: return "Volume Weighted Average Price";
        case CrossType::DefaultTradeWasNotACross: return "Default Trade Was Not A Cross";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
