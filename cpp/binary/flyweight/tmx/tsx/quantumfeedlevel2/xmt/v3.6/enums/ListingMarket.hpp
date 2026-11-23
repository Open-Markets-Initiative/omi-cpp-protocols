// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/ListingMarket.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The Market On Which A Security Is Listed
enum class ListingMarket : char {
    Tsx = 'T',        // Tsx
    TsxVenture = 'V', // Tsx Venture
    TsxNaVex = 'N',   // Tsx Na Vex
    Nasdaq = 'Q',     // Nasdaq
    Nyse = 'S',       // Nyse
    NyseMkt = 'M',    // Nyse Mkt
    NoMarket = 'X',   // No Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ListingMarket value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ListingMarket value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
