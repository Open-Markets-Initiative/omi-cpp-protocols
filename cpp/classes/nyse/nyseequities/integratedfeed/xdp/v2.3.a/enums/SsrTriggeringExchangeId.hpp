#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// This field is only populated when securityStatus = A and this security is listed on this
// exchange. Otherwise it is defaulted to 0x20.
enum class SsrTriggeringExchangeId : char {
    NyseAmerican = 'A', // Nyse American
    NasdaqOmxBx = 'B',  // Nasdaq Omx Bx
    NyseNational = 'C', // Nyse National
    MiamiPearl = 'H',   // Miami Pearl
    NasdaqIse = 'I',    // Nasdaq Ise
    CboeEdga = 'J',     // Cboe Edga
    CboeEdgx = 'K',     // Cboe Edgx
    Ltse = 'L',         // Ltse
    NyseChicago = 'M',  // Nyse Chicago
    Nyse = 'N',         // Nyse
    NyseArca = 'P',     // Nyse Arca
    Nasdaq = 'Q',       // Nasdaq
    NasdaqOmx = 'T',    // Nasdaq Omx
    Memx = 'U',         // Memx
    Iex = 'V',          // Iex
    Cbsx = 'W',         // Cbsx
    NasdaqOmxPsx = 'X', // Nasdaq Omx Psx
    CboeByx = 'Y',      // Cboe Byx
    CboeBzx = 'Z',      // Cboe Bzx
    NoValue = ' ',      // No Value
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SsrTriggeringExchangeId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SsrTriggeringExchangeId value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
