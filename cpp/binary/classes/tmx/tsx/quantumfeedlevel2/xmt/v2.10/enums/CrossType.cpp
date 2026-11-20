// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/CrossType.cpp
#include "CrossType.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(CrossType value) {
    switch (value) {
        case CrossType::Internal: return "Internal";
        case CrossType::Basis: return "Basis";
        case CrossType::Contingent: return "Contingent";
        case CrossType::SpecialTradingSession: return "Special Trading Session";
        case CrossType::VolumeWeightedAveragePrice: return "Volume Weighted Average Price";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CrossType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
