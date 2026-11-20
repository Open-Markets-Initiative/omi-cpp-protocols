// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/SettlementTerms.cpp
#include "SettlementTerms.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(SettlementTerms value) {
    switch (value) {
        case SettlementTerms::Cash: return "Cash";
        case SettlementTerms::Nn: return "Nn";
        case SettlementTerms::Ms: return "Ms";
        case SettlementTerms::Ct: return "Ct";
        case SettlementTerms::ValidSettlementDate: return "Valid Settlement Date";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlementTerms value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
