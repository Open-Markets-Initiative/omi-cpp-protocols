#include "TradeThroughExemption.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(TradeThroughExemption value) {
    switch (value) {
        case TradeThroughExemption::IntermarketSweep: return "Intermarket Sweep";
        case TradeThroughExemption::OpeningPrint: return "Opening Print";
        case TradeThroughExemption::DerivativePriced: return "Derivative Priced";
        case TradeThroughExemption::ReOpeningPrint: return "Re Opening Print";
        case TradeThroughExemption::ClosingPrint: return "Closing Print";
        case TradeThroughExemption::QualifiedContingentTrade: return "Qualified Contingent Trade";
        case TradeThroughExemption::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeThroughExemption value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
