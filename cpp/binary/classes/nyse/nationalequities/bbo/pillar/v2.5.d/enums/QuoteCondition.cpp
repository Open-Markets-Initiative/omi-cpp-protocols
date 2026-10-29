#include "QuoteCondition.hpp"

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

std::string_view to_string(QuoteCondition value) {
    switch (value) {
        case QuoteCondition::RegularQuote: return "Regular Quote";
        case QuoteCondition::OpeningQuote: return "Opening Quote";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nationalequities::bbo::pillar::v2_5_d
