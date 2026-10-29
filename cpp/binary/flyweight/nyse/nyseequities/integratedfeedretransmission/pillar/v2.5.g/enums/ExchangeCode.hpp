#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// For listed equity markets, the market where this symbol is listed.
enum class ExchangeCode : char {
    NyseAmerican = 'A', // Nyse American
    Ltse = 'L',         // Ltse
    NyseTexas = 'M',    // Nyse Texas
    Nyse = 'N',         // Nyse
    NyseArca = 'P',     // Nyse Arca
    Nasdaq = 'Q',       // Nasdaq
    Iex = 'V',          // Iex
    Cboe = 'Z',         // Cboe
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExchangeCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExchangeCode value);

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
