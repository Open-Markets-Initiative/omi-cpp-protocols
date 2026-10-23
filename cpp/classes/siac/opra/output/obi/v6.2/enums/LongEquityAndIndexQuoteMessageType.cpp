#include "LongEquityAndIndexQuoteMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

std::string_view to_string(LongEquityAndIndexQuoteMessageType value) {
    switch (value) {
        case LongEquityAndIndexQuoteMessageType::RegularTrading: return "Regular Trading";
        case LongEquityAndIndexQuoteMessageType::NonFirmQuote: return "Non Firm Quote";
        case LongEquityAndIndexQuoteMessageType::IndicativeValue: return "Indicative Value";
        case LongEquityAndIndexQuoteMessageType::Rotation: return "Rotation";
        case LongEquityAndIndexQuoteMessageType::TradingHalted: return "Trading Halted";
        case LongEquityAndIndexQuoteMessageType::EligibleForAutomaticExecution: return "Eligible For Automatic Execution";
        case LongEquityAndIndexQuoteMessageType::BidContainsCustomerTradingInterest: return "Bid Contains Customer Trading Interest";
        case LongEquityAndIndexQuoteMessageType::OfferContainsCustomerTradingInterest: return "Offer Contains Customer Trading Interest";
        case LongEquityAndIndexQuoteMessageType::BothBidAndOfferContainCustomerTradingInterest: return "Both Bid And Offer Contain Customer Trading Interest";
        case LongEquityAndIndexQuoteMessageType::OfferSideOfQuoteNotFirmBidSideFirm: return "Offer Side Of Quote Not Firm Bid Side Firm";
        case LongEquityAndIndexQuoteMessageType::BidSideOfQuoteNotFirmOfferSideFirm: return "Bid Side Of Quote Not Firm Offer Side Firm";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LongEquityAndIndexQuoteMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::opra::output::obi::v6_2
