#include "QuoteCondition.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

std::string_view to_string(QuoteCondition value) {
    switch (value) {
        case QuoteCondition::RegularQuoteautoxEligible: return "Regular Quoteautox Eligible";
        case QuoteCondition::NonFirmQuote: return "Non Firm Quote";
        case QuoteCondition::RotationalQuote: return "Rotational Quote";
        case QuoteCondition::BidSideFirm: return "Bid Side Firm";
        case QuoteCondition::AskSideFirm: return "Ask Side Firm";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
