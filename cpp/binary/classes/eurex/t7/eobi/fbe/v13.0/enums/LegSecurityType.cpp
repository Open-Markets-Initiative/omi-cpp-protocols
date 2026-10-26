#include "LegSecurityType.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(LegSecurityType value) {
    switch (value) {
        case LegSecurityType::LegSecurityMultiLeg: return "Leg Security Multi Leg";
        case LegSecurityType::LegSecurityUnderlyingLeg: return "Leg Security Underlying Leg";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
