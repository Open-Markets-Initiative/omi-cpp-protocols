#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v1_91 {

// Denotes the sale condition associated with a trade
enum class SaleCondition : char {
    RegularSale = ' ',                                       // Regular Sale
    AveragePriceTrade = 'B',                                 // Average Price Trade
    CashTrade = 'C',                                         // Cash Trade
    AutomaticExecution = 'E',                                // Automatic Execution
    IntermarketSweepOrder = 'F',                             // Intermarket Sweep Order
    PriceVariationTrade = 'H',                               // Price Variation Trade
    OddLotTrade = 'I',                                       // Odd Lot Trade
    Rule127Or155 = 'K',                                      // Rule 127 Or 155
    SoldLast = 'L',                                          // Sold Last
    MarketCenterOfficialClose = 'M',                         // Market Center Official Close
    NextDayTrade = 'N',                                      // Next Day Trade
    MarketCenterOpeningTrade = 'O',                          // Market Center Opening Trade
    PriorReferencePrice = 'P',                               // Prior Reference Price
    MarketCenterOfficialOpen = 'Q',                          // Market Center Official Open
    Seller = 'R',                                            // Seller
    ExtendedHoursTrade = 'T',                                // Extended Hours Trade
    ExtendedHoursSold = 'U',                                 // Extended Hours Sold
    ContingentTrade = 'V',                                   // Contingent Trade
    CrossTrade = 'X',                                        // Cross Trade
    Sold = 'Z',                                              // Sold
    DerivativelyPriced = '4',                                // Derivatively Priced
    MarketCenterReopeningTrade = '5',                        // Market Center Reopening Trade
    MarketCenterClosingTrade = '6',                          // Market Center Closing Trade
    QualifiedContingentTrade = '7',                          // Qualified Contingent Trade
    Reserved = '8',                                          // Reserved
    CorrectedConsolidatedClosePriceAsPerListingMarket = '9', // Corrected Consolidated Close Price As Per Listing Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SaleCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SaleCondition value);

} // namespace siac::cts::output::cta::v1_91
