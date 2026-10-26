#include "SecurityType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(SecurityType value) {
    switch (value) {
        case SecurityType::AmericanDepositaryReceipts: return "American Depositary Receipts";
        case SecurityType::CommonStock: return "Common Stock";
        case SecurityType::Debentures: return "Debentures";
        case SecurityType::ExchangeTradedFunds: return "Exchange Traded Funds";
        case SecurityType::Foreign: return "Foreign";
        case SecurityType::AmericanDepositaryShares: return "American Depositary Shares";
        case SecurityType::Units: return "Units";
        case SecurityType::IndexLinkedNotes: return "Index Linked Notes";
        case SecurityType::OtherBlank: return "Other Blank";
        case SecurityType::OrdinaryShares: return "Ordinary Shares";
        case SecurityType::PreferredStock: return "Preferred Stock";
        case SecurityType::Rights: return "Rights";
        case SecurityType::SharesOfBeneficialInterest: return "Shares Of Beneficial Interest";
        case SecurityType::Test: return "Test";
        case SecurityType::ClosedEndFund: return "Closed End Fund";
        case SecurityType::Warrants: return "Warrants";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
