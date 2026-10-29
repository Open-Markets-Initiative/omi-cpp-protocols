#include "TradeReportingFacilityId.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(TradeReportingFacilityId value) {
    switch (value) {
        case TradeReportingFacilityId::NotApplicable: return "Not Applicable";
        case TradeReportingFacilityId::InactiveValueA: return "Inactive Value A";
        case TradeReportingFacilityId::FinraNasdaqChicago: return "Finra Nasdaq Chicago";
        case TradeReportingFacilityId::InactiveValueC: return "Inactive Value C";
        case TradeReportingFacilityId::InactiveValueD: return "Inactive Value D";
        case TradeReportingFacilityId::InactiveValueI: return "Inactive Value I";
        case TradeReportingFacilityId::InactiveValueJ: return "Inactive Value J";
        case TradeReportingFacilityId::InactiveValueK: return "Inactive Value K";
        case TradeReportingFacilityId::InactiveValueM: return "Inactive Value M";
        case TradeReportingFacilityId::FinraNyse: return "Finra Nyse";
        case TradeReportingFacilityId::InactiveValueP: return "Inactive Value P";
        case TradeReportingFacilityId::FinraNasdaqCarteret: return "Finra Nasdaq Carteret";
        case TradeReportingFacilityId::InactiveValueV: return "Inactive Value V";
        case TradeReportingFacilityId::InactiveValueW: return "Inactive Value W";
        case TradeReportingFacilityId::InactiveValueX: return "Inactive Value X";
        case TradeReportingFacilityId::InactiveValueY: return "Inactive Value Y";
        case TradeReportingFacilityId::InactiveValueZ: return "Inactive Value Z";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeReportingFacilityId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
