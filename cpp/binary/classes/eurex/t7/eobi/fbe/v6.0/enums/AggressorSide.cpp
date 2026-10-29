#include "AggressorSide.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

std::string_view to_string(AggressorSide value) {
    switch (value) {
        case AggressorSide::Buy: return "Buy";
        case AggressorSide::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, AggressorSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v6_0
