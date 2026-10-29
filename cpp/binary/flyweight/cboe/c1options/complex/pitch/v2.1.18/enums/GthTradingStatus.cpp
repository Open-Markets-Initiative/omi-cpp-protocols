#include "GthTradingStatus.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

std::string_view to_string(GthTradingStatus value) {
    switch (value) {
        case GthTradingStatus::Halted: return "Halted";
        case GthTradingStatus::QuoteOnly: return "Quote Only";
        case GthTradingStatus::Trading: return "Trading";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, GthTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
