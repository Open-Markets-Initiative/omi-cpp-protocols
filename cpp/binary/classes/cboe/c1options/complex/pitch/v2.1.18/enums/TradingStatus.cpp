#include "TradingStatus.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

std::string_view to_string(TradingStatus value) {
    switch (value) {
        case TradingStatus::Halted: return "Halted";
        case TradingStatus::QuoteOnly: return "Quote Only";
        case TradingStatus::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
