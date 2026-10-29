#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Options opening will be triggered on receipt of Opening quote/trade from this Underlying
// market:
enum class OpeningUnderlyingMarketCode : char {
    NyseAmex = 'A',          // Nyse Amex
    NasdaqOmxBx = 'B',       // Nasdaq Omx Bx
    Nse = 'C',               // Nse
    FinraAdf = 'D',          // Finra Adf
    MarketIndependent = 'E', // Market Independent
    Ise = 'I',               // Ise
    Edga = 'J',              // Edga
    Edgx = 'K',              // Edgx
    Cse = 'M',               // Cse
    NyseEuronext = 'N',      // Nyse Euronext
    NyseArca = 'P',          // Nyse Arca
    NasdaqOmxUtp = 'Q',      // Nasdaq Omx Utp
    NasdaqOmxCta = 'T',      // Nasdaq Omx Cta
    Iex = 'V',               // Iex
    NasdaqOmxPhlx = 'X',     // Nasdaq Omx Phlx
    BatsY = 'Y',             // Bats Y
    Bats = 'Z',              // Bats
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpeningUnderlyingMarketCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpeningUnderlyingMarketCode value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
