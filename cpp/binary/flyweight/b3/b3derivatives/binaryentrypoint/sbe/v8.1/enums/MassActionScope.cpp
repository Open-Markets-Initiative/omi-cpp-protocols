#include "MassActionScope.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(MassActionScope value) {
    switch (value) {
        case MassActionScope::AllOrdersForATradingSession: return "All Orders For A Trading Session";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MassActionScope value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
