#include "TradingStatus.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::Halted: return "Halted";
        case TradingStatus::CurbTrading: return "Curb Trading";
        case TradingStatus::QuoteOnly: return "Quote Only";
        case TradingStatus::OpeningRotation: return "Opening Rotation";
        case TradingStatus::RthTrading: return "Rth Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
