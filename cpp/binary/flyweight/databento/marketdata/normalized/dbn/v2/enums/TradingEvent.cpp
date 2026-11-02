#include "TradingEvent.hpp"

namespace databento::marketdata::normalized::dbn::v2 {

std::string_view to_string(TradingEvent value) {
    switch (value) {
        case TradingEvent::None: return "None";
        case TradingEvent::NoCancel: return "No Cancel";
        case TradingEvent::ChangeTradingSession: return "Change Trading Session";
        case TradingEvent::ImpliedMatchingOn: return "Implied Matching On";
        case TradingEvent::ImpliedMatchingOff: return "Implied Matching Off";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v2
