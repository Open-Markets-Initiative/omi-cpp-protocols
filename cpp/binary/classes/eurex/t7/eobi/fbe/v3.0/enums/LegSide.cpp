#include "LegSide.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::Buy: return "Buy";
        case LegSide::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v3_0
