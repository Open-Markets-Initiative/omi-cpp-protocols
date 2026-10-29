#include "IssueClassification.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(IssueClassification value) {
    switch (value) {
        case IssueClassification::AmericanDepositaryShare: return "American Depositary Share";
        case IssueClassification::Bond: return "Bond";
        case IssueClassification::CommonStock: return "Common Stock";
        case IssueClassification::DepositoryReceipt: return "Depository Receipt";
        case IssueClassification::Rule144A: return "Rule 144 A";
        case IssueClassification::LimitedPartnership: return "Limited Partnership";
        case IssueClassification::Notes: return "Notes";
        case IssueClassification::OrdinaryShare: return "Ordinary Share";
        case IssueClassification::PreferredStock: return "Preferred Stock";
        case IssueClassification::OtherSecurities: return "Other Securities";
        case IssueClassification::Right: return "Right";
        case IssueClassification::SharesOfBeneficialInterest: return "Shares Of Beneficial Interest";
        case IssueClassification::ConvertibleDebenture: return "Convertible Debenture";
        case IssueClassification::Unit: return "Unit";
        case IssueClassification::UnitsOfBeneficialInterest: return "Units Of Beneficial Interest";
        case IssueClassification::Warrant: return "Warrant";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IssueClassification value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
