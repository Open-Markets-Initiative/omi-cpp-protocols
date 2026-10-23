#include "TradingStatus.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::AcceptingOrdersForQueuing: return "Accepting Orders For Queuing";
        case TradingStatus::Halted: return "Halted";
        case TradingStatus::QuoteOnly: return "Quote Only";
        case TradingStatus::ExchangeSpecificSuspension: return "Exchange Specific Suspension";
        case TradingStatus::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29
