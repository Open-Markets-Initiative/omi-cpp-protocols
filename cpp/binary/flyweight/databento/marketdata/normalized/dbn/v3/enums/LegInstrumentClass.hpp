#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// The classification of the leg instrument
enum class LegInstrumentClass : char {
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
std::string_view to_string(LegInstrumentClass value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegInstrumentClass value);

} // namespace databento::marketdata::normalized::dbn::v3
