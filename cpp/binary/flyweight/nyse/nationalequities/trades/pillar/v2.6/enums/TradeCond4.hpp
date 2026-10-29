#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// SRO Required Detail.
enum class TradeCond4 : char {
    Na = ' ',                            // Na
    OddLotTrade = 'I',                   // Odd Lot Trade
    OfficialClosingPrice = 'M',          // Official Closing Price
    OfficialOpenPrice = 'Q',             // Official Open Price
    ContingentTradeTrfOrTexasOnly = 'V', // Contingent Trade Trf Or Texas Only
    PriorReferencePriceTrfOnly = 'P',    // Prior Reference Price Trf Only
    WeightedAveragePriceTrfOnly = 'W',   // Weighted Average Price Trf Only
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCond4 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCond4 value);

} // namespace nyse::nationalequities::trades::pillar::v2_6
