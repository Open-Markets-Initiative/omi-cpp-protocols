#include "OriginalTradeThroughExemption.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(OriginalTradeThroughExemption value) {
    switch (value) {
        case OriginalTradeThroughExemption::IntermarketSweep: return "Intermarket Sweep";
        case OriginalTradeThroughExemption::OpeningPrint: return "Opening Print";
        case OriginalTradeThroughExemption::DerivativePriced: return "Derivative Priced";
        case OriginalTradeThroughExemption::ReOpeningPrint: return "Re Opening Print";
        case OriginalTradeThroughExemption::ClosingPrint: return "Closing Print";
        case OriginalTradeThroughExemption::QualifiedContingentTrade: return "Qualified Contingent Trade";
        case OriginalTradeThroughExemption::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OriginalTradeThroughExemption value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
