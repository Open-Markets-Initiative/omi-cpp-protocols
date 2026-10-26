#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Denotes the sale condition associated with a trade
enum class SaleCondition1 : char {
    RegularSale = ' ',                                       // Regular Sale
    AveragePriceTrade = 'B',                                 // Average Price Trade
    CashTradeSameDayClearing = 'C',                          // Cash Trade Same Day Clearing
    AutomaticExecution = 'E',                                // Automatic Execution
    IntermarketSweepOrder = 'F',                             // Intermarket Sweep Order
    PriceVariationTrade = 'H',                               // Price Variation Trade
    OddLotTrade = 'I',                                       // Odd Lot Trade
    Rule127NyseOnlyOrRule155NyseAmericanOnly = 'K',          // Rule 127 Nyse Only Or Rule 155 Nyse American Only
    SoldLastLateReporting = 'L',                             // Sold Last Late Reporting
    MarketCenterOfficialClose = 'M',                         // Market Center Official Close
    ReservedN = 'N',                                         // Reserved N
    MarketCenterOpeningTrade = 'O',                          // Market Center Opening Trade
    PriorReferencePrice = 'P',                               // Prior Reference Price
    MarketCenterOfficialOpen = 'Q',                          // Market Center Official Open
    Seller = 'R',                                            // Seller
    ExtendedHoursTrade = 'T',                                // Extended Hours Trade
    ExtendedHoursSoldOutOfSequence = 'U',                    // Extended Hours Sold Out Of Sequence
    ContingentTrade = 'V',                                   // Contingent Trade
    CrossPeriodicAuctionTrade = 'X',                         // Cross Periodic Auction Trade
    SoldOutOfSequence = 'Z',                                 // Sold Out Of Sequence
    DerivativelyPriced = '4',                                // Derivatively Priced
    MarketCenterReopeningTrade = '5',                        // Market Center Reopening Trade
    MarketCenterClosingTrade = '6',                          // Market Center Closing Trade
    QualifiedContingentTrade = '7',                          // Qualified Contingent Trade
    Reserved8 = '8',                                         // Reserved 8
    CorrectedConsolidatedClosePriceAsPerListingMarket = '9', // Corrected Consolidated Close Price As Per Listing Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SaleCondition1 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SaleCondition1 value);

} // namespace siac::cts::output::cta::v2_11_b
