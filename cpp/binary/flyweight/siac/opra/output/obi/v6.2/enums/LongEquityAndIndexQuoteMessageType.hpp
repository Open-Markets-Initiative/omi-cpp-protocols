#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Long Equity and Index Quote Message Type
enum class LongEquityAndIndexQuoteMessageType : char {
    RegularTrading = ' ',                                // Regular Trading
    NonFirmQuote = 'F',                                  // Non Firm Quote
    IndicativeValue = 'I',                               // Indicative Value
    Rotation = 'R',                                      // Rotation
    TradingHalted = 'T',                                 // Trading Halted
    EligibleForAutomaticExecution = 'A',                 // Eligible For Automatic Execution
    BidContainsCustomerTradingInterest = 'B',            // Bid Contains Customer Trading Interest
    OfferContainsCustomerTradingInterest = 'O',          // Offer Contains Customer Trading Interest
    BothBidAndOfferContainCustomerTradingInterest = 'C', // Both Bid And Offer Contain Customer Trading Interest
    OfferSideOfQuoteNotFirmBidSideFirm = 'X',            // Offer Side Of Quote Not Firm Bid Side Firm
    BidSideOfQuoteNotFirmOfferSideFirm = 'Y',            // Bid Side Of Quote Not Firm Offer Side Firm
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LongEquityAndIndexQuoteMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LongEquityAndIndexQuoteMessageType value);

} // namespace siac::opra::output::obi::v6_2
