#include "AllocReportType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(AllocReportType value) {
    switch (value) {
        case AllocReportType::RequestToIntermediary: return "Request To Intermediary";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AllocReportType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
