#include "ShortEquityAndIndexQuoteMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(ShortEquityAndIndexQuoteMessageType value) {
    switch (value) {
        case ShortEquityAndIndexQuoteMessageType::RegularTrading: return "Regular Trading";
        case ShortEquityAndIndexQuoteMessageType::NonFirmQuote: return "Non Firm Quote";
        case ShortEquityAndIndexQuoteMessageType::IndicativeValue: return "Indicative Value";
        case ShortEquityAndIndexQuoteMessageType::Rotation: return "Rotation";
        case ShortEquityAndIndexQuoteMessageType::TradingHalted: return "Trading Halted";
        case ShortEquityAndIndexQuoteMessageType::EligibleForAutomaticExecution: return "Eligible For Automatic Execution";
        case ShortEquityAndIndexQuoteMessageType::BidContainsCustomerTradingInterest: return "Bid Contains Customer Trading Interest";
        case ShortEquityAndIndexQuoteMessageType::OfferContainsCustomerTradingInterest: return "Offer Contains Customer Trading Interest";
        case ShortEquityAndIndexQuoteMessageType::BothBidAndOfferContainCustomerTradingInterest: return "Both Bid And Offer Contain Customer Trading Interest";
        case ShortEquityAndIndexQuoteMessageType::OfferSideOfQuoteNotFirmBidSideFirm: return "Offer Side Of Quote Not Firm Bid Side Firm";
        case ShortEquityAndIndexQuoteMessageType::BidSideOfQuoteNotFirmOfferSideFirm: return "Bid Side Of Quote Not Firm Offer Side Firm";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortEquityAndIndexQuoteMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
