#include "SettlementCondition.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(SettlementCondition value) {
    switch (value) {
        case SettlementCondition::RegularWaySettlement: return "Regular Way Settlement";
        case SettlementCondition::CashOnlySettlement: return "Cash Only Settlement";
        case SettlementCondition::NextDayOnlySettlement: return "Next Day Only Settlement";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlementCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
