#include "QuoteCondition.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

std::string_view to_string(QuoteCondition value) {
    switch (value) {
        case QuoteCondition::Closing: return "Closing";
        case QuoteCondition::OpeningQuote: return "Opening Quote";
        case QuoteCondition::RegularQuote: return "Regular Quote";
        case QuoteCondition::SlowOnTheBidAndAsk: return "Slow On The Bid And Ask";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaequities::bbo::xdp::v2_4_c
