#include "TradingSessionId.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::string_view to_string(TradingSessionId value) {
    switch (value) {
        case TradingSessionId::Day: return "Day";
        case TradingSessionId::Morning: return "Morning";
        case TradingSessionId::Evening: return "Evening";
        case TradingSessionId::Holiday: return "Holiday";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingSessionId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace bse::bseindia::eobi::fbe::v1_4
