#include "TimeInForce.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(TimeInForce value) {
    switch (value) {
        case TimeInForce::Immediate: return "Immediate";
        case TimeInForce::Day: return "Day";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TimeInForce value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
