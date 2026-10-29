#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

enum class EopType : std::uint8_t {
    Undefined = 0,             // Undefined
    OpeningPrice = 1,          // Opening Price
    NeedMoreSellers = 2,       // Need More Sellers
    NeedMoreBuyers = 3,        // Need More Buyers
    NoOpeningTrades = 4,       // No Opening Trades
    MultipleOpeningPrices = 5, // Multiple Opening Prices
    NeedQuoteToOpen = 6,       // Need Quote To Open
    PriceNotInQuoteRange = 7,  // Price Not In Quote Range
    NeedDpmQuoteToOpen = 8,    // Need Dpm Quote To Open
    DpmQuoteInvalid = 9,       // Dpm Quote Invalid
    PriceNotInBotrRange = 10,  // Price Not In Botr Range
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EopType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EopType value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
