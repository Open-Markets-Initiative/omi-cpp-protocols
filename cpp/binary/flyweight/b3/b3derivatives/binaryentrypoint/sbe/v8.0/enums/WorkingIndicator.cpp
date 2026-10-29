#include "WorkingIndicator.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(WorkingIndicator value) {
    switch (value) {
        case WorkingIndicator::FalseValue: return "False Value";
        case WorkingIndicator::TrueValue: return "True Value";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, WorkingIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
