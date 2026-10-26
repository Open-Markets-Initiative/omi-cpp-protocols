#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class InstrumentScopeProductComplex : std::uint8_t {
    SimpleInstrument = 1,               // Simple Instrument
    StandardOptionStrategy = 2,         // Standard Option Strategy
    NonStandardOptionStrategy = 3,      // Non Standard Option Strategy
    VolatilityStrategy = 4,             // Volatility Strategy
    FuturesSpread = 5,                  // Futures Spread
    InterProductSpread = 6,             // Inter Product Spread
    StandardFuturesStrategy = 7,        // Standard Futures Strategy
    PackAndBundle = 8,                  // Pack And Bundle
    Strip = 9,                          // Strip
    FlexibleInstrument = 10,            // Flexible Instrument
    CommodityStrip = 11,                // Commodity Strip
    ScaledSimpleInstrument = 12,        // Scaled Simple Instrument
    NonStandardVolatilityStrategy = 13, // Non Standard Volatility Strategy
    TotalReturnFutureStrategy = 14,     // Total Return Future Strategy
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InstrumentScopeProductComplex value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InstrumentScopeProductComplex value);

} // namespace eurex::t7::eobi::fbe::v15_0
