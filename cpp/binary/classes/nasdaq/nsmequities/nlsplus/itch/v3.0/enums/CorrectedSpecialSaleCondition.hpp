#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Used for special sale condition codes. This field is case sensitive
enum class CorrectedSpecialSaleCondition : char {
    Acquisition = 'A',                // Acquisition
    Bunched = 'B',                    // Bunched
    Distribution = 'D',               // Distribution
    PriceVariationTransaction = 'H',  // Price Variation Transaction
    NasdaqOfficialClosePrice = 'M',   // Nasdaq Official Close Price
    PriorReferencePrice = 'P',        // Prior Reference Price
    NasdaqOfficialOpeningPrice = 'Q', // Nasdaq Official Opening Price
    SplitTrade = 'S',                 // Split Trade
    ContingentTrade = 'V',            // Contingent Trade
    AveragePriceTrade = 'W',          // Average Price Trade
    CrossTrade = 'X',                 // Cross Trade
    OddLotExecution = 'o',            // Odd Lot Execution
    OddLotCrossExecution = 'x',       // Odd Lot Cross Execution
    NotApplicable = ' ',              // Not Applicable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CorrectedSpecialSaleCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CorrectedSpecialSaleCondition value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
