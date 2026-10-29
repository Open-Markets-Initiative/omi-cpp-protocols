#include "IssueClassification.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(IssueClassification value) {
    switch (value) {
        case IssueClassification::AmericanDepositaryShare: return "American Depositary Share";
        case IssueClassification::Bond: return "Bond";
        case IssueClassification::CommonStock: return "Common Stock";
        case IssueClassification::DepositoryReceipt: return "Depository Receipt";
        case IssueClassification::Sec144A: return "Sec 144 A";
        case IssueClassification::LimitedPartnership: return "Limited Partnership";
        case IssueClassification::Notes: return "Notes";
        case IssueClassification::OrdinaryShare: return "Ordinary Share";
        case IssueClassification::PreferredStock: return "Preferred Stock";
        case IssueClassification::OtherSecurities: return "Other Securities";
        case IssueClassification::Right: return "Right";
        case IssueClassification::SharesOfBeneficialInterest: return "Shares Of Beneficial Interest";
        case IssueClassification::ConvertibleDebenture: return "Convertible Debenture";
        case IssueClassification::Unit: return "Unit";
        case IssueClassification::UnitsBenifInt: return "Units Benif Int";
        case IssueClassification::Warrant: return "Warrant";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IssueClassification value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
