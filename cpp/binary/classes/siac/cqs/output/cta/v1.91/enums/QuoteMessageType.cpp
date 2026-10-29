#include "QuoteMessageType.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(QuoteMessageType value) {
    switch (value) {
        case QuoteMessageType::AuctionStatusMessage: return "Auction Status Message";
        case QuoteMessageType::LongQuoteMessage: return "Long Quote Message";
        case QuoteMessageType::ShortQuoteMessage: return "Short Quote Message";
        case QuoteMessageType::SpecialLongQuoteMessage: return "Special Long Quote Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, QuoteMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
