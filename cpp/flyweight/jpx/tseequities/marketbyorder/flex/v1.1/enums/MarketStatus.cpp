#include "MarketStatus.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

std::string_view to_string(MarketStatus value) {
    switch (value) {
        case MarketStatus::MorningSessionOrderAcceptanceTime: return "Morning Session Order Acceptance Time";
        case MarketStatus::MorningSessionTradingHours: return "Morning Session Trading Hours";
        case MarketStatus::EndOfMorningSession: return "End Of Morning Session";
        case MarketStatus::AfternoonSessionOrderAcceptanceTime: return "Afternoon Session Order Acceptance Time";
        case MarketStatus::AfternoonSessionTradingHours: return "Afternoon Session Trading Hours";
        case MarketStatus::AfternoonSessionPreclosing: return "Afternoon Session Preclosing";
        case MarketStatus::EndOfAfternoonSession: return "End Of Afternoon Session";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
