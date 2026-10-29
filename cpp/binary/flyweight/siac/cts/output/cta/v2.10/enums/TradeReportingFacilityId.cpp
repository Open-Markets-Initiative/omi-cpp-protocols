#include "TradeReportingFacilityId.hpp"

namespace siac::cts::output::cta::v2_10 {

std::string_view to_string(TradeReportingFacilityId value) {
    switch (value) {
        case TradeReportingFacilityId::NotApplicable: return "Not Applicable";
        case TradeReportingFacilityId::FinraNasdaqChicago: return "Finra Nasdaq Chicago";
        case TradeReportingFacilityId::FinraNyse: return "Finra Nyse";
        case TradeReportingFacilityId::FinraNasdaqCarteret: return "Finra Nasdaq Carteret";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeReportingFacilityId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_10
