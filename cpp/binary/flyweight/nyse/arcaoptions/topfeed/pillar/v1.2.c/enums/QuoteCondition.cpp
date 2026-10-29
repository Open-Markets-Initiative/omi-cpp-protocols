#include "QuoteCondition.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(QuoteCondition value) {
    switch (value) {
        case QuoteCondition::RegularTrading: return "Regular Trading";
        case QuoteCondition::Rotation: return "Rotation";
        case QuoteCondition::TradingHalted: return "Trading Halted";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
