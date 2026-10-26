#include "MultiLegReportingType.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(MultiLegReportingType value) {
    switch (value) {
        case MultiLegReportingType::SingleSecurity: return "Single Security";
        case MultiLegReportingType::IndividualLegOfAMultiLegSecurity: return "Individual Leg Of A Multi Leg Security";
        case MultiLegReportingType::MultiLegSecurity: return "Multi Leg Security";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MultiLegReportingType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
