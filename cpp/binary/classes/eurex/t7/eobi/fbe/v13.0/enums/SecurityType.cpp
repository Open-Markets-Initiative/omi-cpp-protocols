#include "SecurityType.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(SecurityType value) {
    switch (value) {
        case SecurityType::Opt: return "Opt";
        case SecurityType::Fut: return "Fut";
        case SecurityType::Mleg: return "Mleg";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
