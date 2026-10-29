#include "SecurityType.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

std::string_view to_string(SecurityType value) {
    switch (value) {
        case SecurityType::Adr: return "Adr";
        case SecurityType::CommonStock: return "Common Stock";
        case SecurityType::Debentures: return "Debentures";
        case SecurityType::Etf: return "Etf";
        case SecurityType::Foreign: return "Foreign";
        case SecurityType::AmericanDepositoryShares: return "American Depository Shares";
        case SecurityType::Units: return "Units";
        case SecurityType::MiscliquidTrust: return "Miscliquid Trust";
        case SecurityType::OrdinaryShares: return "Ordinary Shares";
        case SecurityType::PreferredStock: return "Preferred Stock";
        case SecurityType::Rights: return "Rights";
        case SecurityType::SharesOfBeneficiaryInterest: return "Shares Of Beneficiary Interest";
        case SecurityType::Test: return "Test";
        case SecurityType::Units2: return "Units";
        case SecurityType::Warrant: return "Warrant";
        case SecurityType::Index: return "Index";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
