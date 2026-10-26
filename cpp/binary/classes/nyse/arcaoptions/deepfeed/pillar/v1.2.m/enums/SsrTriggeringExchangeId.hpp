#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Only populated when securityStatus = A and this security is listed on this exchange.
// Otherwise defaulted to space (0x20).
enum class SsrTriggeringExchangeId : char {
    NyseAmerican = 'A', // Nyse American
    NasdaqOmxBx = 'B',  // Nasdaq Omx Bx
    NyseNational = 'C', // Nyse National
    Finra = 'D',        // Finra
    Txse = 'F',         // Txse
    N24x = 'G',         // N24X
    Ise = 'I',          // Ise
    CboeEdga = 'J',     // Cboe Edga
    CboeEdgx = 'K',     // Cboe Edgx
    Ltse = 'L',         // Ltse
    NyseTexas = 'M',    // Nyse Texas
    Nyse = 'N',         // Nyse
    NyseArca = 'P',     // Nyse Arca
    Nasdaq = 'Q',       // Nasdaq
    Cts = 'S',          // Cts
    NasdaqOmx = 'T',    // Nasdaq Omx
    Iex = 'V',          // Iex
    Cbsx = 'W',         // Cbsx
    NasdaqOmxPsx = 'X', // Nasdaq Omx Psx
    CboeByx = 'Y',      // Cboe Byx
    CboeBzx = 'Z',      // Cboe Bzx
    Miax = 'H',         // Miax
    Memx = 'U',         // Memx
    NoValue = ' ',      // No Value
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SsrTriggeringExchangeId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SsrTriggeringExchangeId value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
