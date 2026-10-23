#include "SettlMethod.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(SettlMethod value) {
    switch (value) {
        case SettlMethod::Cash: return "Cash";
        case SettlMethod::Physical: return "Physical";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlMethod value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
