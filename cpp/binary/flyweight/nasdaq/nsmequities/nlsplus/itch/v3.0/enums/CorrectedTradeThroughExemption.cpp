#include "CorrectedTradeThroughExemption.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(CorrectedTradeThroughExemption value) {
    switch (value) {
        case CorrectedTradeThroughExemption::IntermarketSweep: return "Intermarket Sweep";
        case CorrectedTradeThroughExemption::OpeningPrint: return "Opening Print";
        case CorrectedTradeThroughExemption::DerivativePriced: return "Derivative Priced";
        case CorrectedTradeThroughExemption::ReOpeningPrint: return "Re Opening Print";
        case CorrectedTradeThroughExemption::ClosingPrint: return "Closing Print";
        case CorrectedTradeThroughExemption::QualifiedContingentTrade: return "Qualified Contingent Trade";
        case CorrectedTradeThroughExemption::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CorrectedTradeThroughExemption value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
