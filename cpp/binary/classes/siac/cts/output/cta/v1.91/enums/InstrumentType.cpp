#include "InstrumentType.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(InstrumentType value) {
    switch (value) {
        case InstrumentType::CtaEligibleEquity: return "Cta Eligible Equity";
        case InstrumentType::LocalIssue: return "Local Issue";
        case InstrumentType::CorporateBond: return "Corporate Bond";
        case InstrumentType::GovernmentBond: return "Government Bond";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InstrumentType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
