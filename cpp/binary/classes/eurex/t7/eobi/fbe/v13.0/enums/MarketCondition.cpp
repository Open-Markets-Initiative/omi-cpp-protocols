#include "MarketCondition.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(MarketCondition value) {
    switch (value) {
        case MarketCondition::Normal: return "Normal";
        case MarketCondition::Stressed: return "Stressed";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
