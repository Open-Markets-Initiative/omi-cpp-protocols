#include "TradingStatus.hpp"

namespace iex::iexequities::deepplus::snap::v1_06 {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::TradingHaltedAcrossAllUsEquityMarkets: return "Trading Halted Across All Us Equity Markets";
        case TradingStatus::TradingHaltReleasedIntoAnOrderAcceptancePeriodOnIex: return "Trading Halt Released Into An Order Acceptance Period On Iex";
        case TradingStatus::TradingPausedAndOrderAcceptancePeriodOnIex: return "Trading Paused And Order Acceptance Period On Iex";
        case TradingStatus::TradingOnIex: return "Trading On Iex";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deepplus::snap::v1_06
