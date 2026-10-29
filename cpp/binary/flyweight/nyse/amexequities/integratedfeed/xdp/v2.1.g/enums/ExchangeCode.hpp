#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// For listed equity markets, the market where this symbol is listed
enum class ExchangeCode : char {
    NyseAmerican = 'A', // Nyse American
    NyseNational = 'C', // Nyse National
    Nyse = 'N',         // Nyse
    NyseArca = 'P',     // Nyse Arca
    Nasdaq = 'Q',       // Nasdaq
    Iex = 'V',          // Iex
    Bats = 'Z',         // Bats
    GlobalOtc = 'B',    // Global Otc
    Otcbb = 'U',        // Otcbb
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExchangeCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExchangeCode value);

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
