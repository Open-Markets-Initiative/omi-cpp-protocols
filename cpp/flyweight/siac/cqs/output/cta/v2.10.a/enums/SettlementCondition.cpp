#include "SettlementCondition.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(SettlementCondition value) {
    switch (value) {
        case SettlementCondition::RegularWaySettlement: return "Regular Way Settlement";
        case SettlementCondition::CashSettlement: return "Cash Settlement";
        case SettlementCondition::NextDaySettlement: return "Next Day Settlement";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlementCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
