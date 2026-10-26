#include "TradingSessionId.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(TradingSessionId value) {
    switch (value) {
        case TradingSessionId::Day: return "Day";
        case TradingSessionId::Morning: return "Morning";
        case TradingSessionId::Evening: return "Evening";
        case TradingSessionId::AfterHours: return "After Hours";
        case TradingSessionId::Holiday: return "Holiday";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingSessionId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
