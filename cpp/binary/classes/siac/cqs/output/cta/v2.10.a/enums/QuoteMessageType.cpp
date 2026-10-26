#include "QuoteMessageType.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(QuoteMessageType value) {
    switch (value) {
        case QuoteMessageType::AuctionStatus: return "Auction Status";
        case QuoteMessageType::LongQuote: return "Long Quote";
        case QuoteMessageType::ShortQuote: return "Short Quote";
        case QuoteMessageType::SpecialLongQuote: return "Special Long Quote";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
