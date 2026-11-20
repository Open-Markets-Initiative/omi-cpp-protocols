// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/InitiatedBy.cpp
#include "InitiatedBy.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

std::string_view to_string(InitiatedBy value) {
    switch (value) {
        case InitiatedBy::Buy: return "Buy";
        case InitiatedBy::Sell: return "Sell";
        case InitiatedBy::Both: return "Both";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InitiatedBy value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
