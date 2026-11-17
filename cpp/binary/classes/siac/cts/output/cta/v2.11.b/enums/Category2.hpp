// Siac.Cts.Output.Cta.v2.11.b: enums/Category2.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Reason for Trade-Through Exemption / Other Reason
enum class Category2 : char {
    NoTradeThroughExemptReason = ' ',                        // No Trade Through Exempt Reason
    InterMarketSweepOrder = 'F',                             // Inter Market Sweep Order
    MarketCenterOpeningTrade = 'O',                          // Market Center Opening Trade
    DerivativelyPriced = '4',                                // Derivatively Priced
    MarketCenterReopeningTrade = '5',                        // Market Center Reopening Trade
    MarketCenterClosingTrade = '6',                          // Market Center Closing Trade
    QualifiedContingentTrade = '7',                          // Qualified Contingent Trade
    Reserved = '8',                                          // Reserved
    CorrectedConsolidatedClosePriceAsPerListingMarket = '9', // Corrected Consolidated Close Price As Per Listing Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Category2 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Category2 value);

} // namespace siac::cts::output::cta::v2_11_b
