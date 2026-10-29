#include "MultiLegReportingType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(MultiLegReportingType value) {
    switch (value) {
        case MultiLegReportingType::SingleSecurity: return "Single Security";
        case MultiLegReportingType::IndividuallegOfMultilegSecurity: return "Individualleg Of Multileg Security";
        case MultiLegReportingType::MultilegSecurity: return "Multileg Security";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MultiLegReportingType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
