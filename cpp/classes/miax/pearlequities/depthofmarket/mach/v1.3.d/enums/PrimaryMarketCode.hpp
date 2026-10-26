#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Primary listing exchange code for the security.
enum class PrimaryMarketCode : char {
    NyseAmerican = 'A',          // Nyse American
    NasdaqTexas = 'B',           // Nasdaq Texas
    NyseNational = 'C',          // Nyse National
    TexasStockExchange = 'F',    // Texas Stock Exchange
    N24xExchange = 'G',          // N24X Exchange
    MiaxPearlEquities = 'H',     // Miax Pearl Equities
    NasdaqIse = 'I',             // Nasdaq Ise
    CboeEdgaExchange = 'J',      // Cboe Edga Exchange
    CboeEdgxExchange = 'K',      // Cboe Edgx Exchange
    LongTermStockExchange = 'L', // Long Term Stock Exchange
    NyseTexas = 'M',             // Nyse Texas
    NewYorkStockExchange = 'N',  // New York Stock Exchange
    NyseArca = 'P',              // Nyse Arca
    Nasdaq = 'Q',                // Nasdaq
    MembersExchange = 'U',       // Members Exchange
    InvestorsExchange = 'V',     // Investors Exchange
    CboeStockExchange = 'W',     // Cboe Stock Exchange
    NasdaqPhlx = 'X',            // Nasdaq Phlx
    CboeByxExchange = 'Y',       // Cboe Byx Exchange
    CboeBzxExchange = 'Z',       // Cboe Bzx Exchange
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PrimaryMarketCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PrimaryMarketCode value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
