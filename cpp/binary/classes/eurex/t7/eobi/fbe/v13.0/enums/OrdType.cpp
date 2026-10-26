#include "OrdType.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(OrdType value) {
    switch (value) {
        case OrdType::Market: return "Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrdType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
