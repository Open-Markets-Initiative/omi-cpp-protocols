#include "TradeReportingFacilityId.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(TradeReportingFacilityId value) {
    switch (value) {
        case TradeReportingFacilityId::TrfNotApplicable: return "Trf Not Applicable";
        case TradeReportingFacilityId::NotCurrentlyActiveA: return "Not Currently Active A";
        case TradeReportingFacilityId::FinraNasdaqTrfChicago: return "Finra Nasdaq Trf Chicago";
        case TradeReportingFacilityId::NotCurrentlyActiveC: return "Not Currently Active C";
        case TradeReportingFacilityId::NotCurrentlyActiveD: return "Not Currently Active D";
        case TradeReportingFacilityId::NotCurrentlyActiveI: return "Not Currently Active I";
        case TradeReportingFacilityId::NotCurrentlyActiveJ: return "Not Currently Active J";
        case TradeReportingFacilityId::NotCurrentlyActiveK: return "Not Currently Active K";
        case TradeReportingFacilityId::NotCurrentlyActiveM: return "Not Currently Active M";
        case TradeReportingFacilityId::FinraNyseTrf: return "Finra Nyse Trf";
        case TradeReportingFacilityId::NotCurrentlyActiveP: return "Not Currently Active P";
        case TradeReportingFacilityId::FinraNasdaqTrfCarteret: return "Finra Nasdaq Trf Carteret";
        case TradeReportingFacilityId::NotCurrentlyActiveV: return "Not Currently Active V";
        case TradeReportingFacilityId::NotCurrentlyActiveW: return "Not Currently Active W";
        case TradeReportingFacilityId::NotCurrentlyActiveX: return "Not Currently Active X";
        case TradeReportingFacilityId::NotCurrentlyActiveY: return "Not Currently Active Y";
        case TradeReportingFacilityId::NotCurrentlyActiveZ: return "Not Currently Active Z";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeReportingFacilityId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
