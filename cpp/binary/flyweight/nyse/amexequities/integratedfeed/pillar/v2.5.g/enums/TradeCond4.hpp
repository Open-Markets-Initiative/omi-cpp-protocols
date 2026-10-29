#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

// SRO Required Detail.
enum class TradeCond4 : char {
    Na = ' ',                       // Na
    OddLotTrade = 'I',              // Odd Lot Trade
    ContingentTradeTexasOnly = 'V', // Contingent Trade Texas Only
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCond4 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCond4 value);

} // namespace nyse::amexequities::integratedfeed::pillar::v2_5_g
