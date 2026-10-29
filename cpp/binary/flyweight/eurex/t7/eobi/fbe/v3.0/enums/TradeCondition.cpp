#include "TradeCondition.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

std::string_view to_string(TradeCondition value) {
    switch (value) {
        case TradeCondition::ImpliedTrade: return "Implied Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v3_0
