#include "QuoteCondition.hpp"

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

std::string_view to_string(QuoteCondition value) {
    switch (value) {
        case QuoteCondition::OpeningQuote: return "Opening Quote";
        case QuoteCondition::RegularQuote: return "Regular Quote";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::bbo::pillar::v2_5_b
