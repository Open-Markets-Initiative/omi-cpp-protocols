// Databento.MarketData.Normalized.Dbn.v2: enums/InstrumentClass.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v2 {

// The classification of the instrument
enum class InstrumentClass : char {
    Bond = 'B',          // Bond
    Call = 'C',          // Call
    Future = 'F',        // Future
    Index = 'I',         // Index
    Stock = 'K',         // Stock
    MixedSpread = 'M',   // Mixed Spread
    Put = 'P',           // Put
    FutureSpread = 'S',  // Future Spread
    OptionSpread = 'T',  // Option Spread
    FxSpot = 'X',        // Fx Spot
    CommoditySpot = 'Y', // Commodity Spot
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InstrumentClass value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InstrumentClass value);

} // namespace databento::marketdata::normalized::dbn::v2
