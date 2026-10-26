#include "TradingStatus.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::Suspended: return "Suspended";
        case TradingStatus::Queuing: return "Queuing";
        case TradingStatus::Trading: return "Trading";
        case TradingStatus::Halted: return "Halted";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
