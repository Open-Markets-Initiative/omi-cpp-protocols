#include "SecurityType.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(SecurityType value) {
    switch (value) {
        case SecurityType::Adr: return "Adr";
        case SecurityType::CommonStock: return "Common Stock";
        case SecurityType::Debentures: return "Debentures";
        case SecurityType::Etf: return "Etf";
        case SecurityType::Foreign: return "Foreign";
        case SecurityType::UsDepositaryShares: return "Us Depositary Shares";
        case SecurityType::Units: return "Units";
        case SecurityType::IndexLinkedNotes: return "Index Linked Notes";
        case SecurityType::MiscliquidTrust: return "Miscliquid Trust";
        case SecurityType::OrdinaryShares: return "Ordinary Shares";
        case SecurityType::PreferredStock: return "Preferred Stock";
        case SecurityType::Rights: return "Rights";
        case SecurityType::SharesOfBeneficiaryInterest: return "Shares Of Beneficiary Interest";
        case SecurityType::Test: return "Test";
        case SecurityType::ClosedEndFund: return "Closed End Fund";
        case SecurityType::Warrant: return "Warrant";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
