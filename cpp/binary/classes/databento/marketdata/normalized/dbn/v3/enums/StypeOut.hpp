#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// The output symbology type
enum class StypeOut : std::uint8_t {
    InstrumentId = 0,   // Instrument Id
    RawSymbol = 1,      // Raw Symbol
    Smart = 2,          // Smart
    Continuous = 3,     // Continuous
    Parent = 4,         // Parent
    NasdaqSymbol = 5,   // Nasdaq Symbol
    CmsSymbol = 6,      // Cms Symbol
    Isin = 7,           // Isin
    UsCode = 8,         // Us Code
    BbgCompId = 9,      // Bbg Comp Id
    BbgCompTicker = 10, // Bbg Comp Ticker
    Figi = 11,          // Figi
    FigiTicker = 12,    // Figi Ticker
    ListingId = 13,     // Listing Id
    IssuerId = 14,      // Issuer Id
    SecurityId = 15,    // Security Id
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StypeOut value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StypeOut value);

} // namespace databento::marketdata::normalized::dbn::v3
