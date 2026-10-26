#include "GthTradingStatus.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

std::string_view to_string(GthTradingStatus value) {
    switch (value) {
        case GthTradingStatus::Halted: return "Halted";
        case GthTradingStatus::QuoteOnly: return "Quote Only";
        case GthTradingStatus::OpeningRotation: return "Opening Rotation";
        case GthTradingStatus::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, GthTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
