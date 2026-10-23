#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the Participant or Processor that initiated the message
enum class ParticipantId : char {
    NyseAmericanLlcNyseAmerican = 'A',           // Nyse American Llc Nyse American
    NasdaqOmxBxIncNasdaqOmxBx = 'B',             // Nasdaq Omx Bx Inc Nasdaq Omx Bx
    NyseNationalIncNyseNational = 'C',           // Nyse National Inc Nyse National
    FinraAlternativeDisplayFacilityAdf = 'D',    // Finra Alternative Display Facility Adf
    TexasStockExchangeLlcTxse = 'F',             // Texas Stock Exchange Llc Txse
    N24xNationalExchangeLlc24X = 'G',            // N24X National Exchange LLC 24X
    MiaxPearlExchangeLlcMiax = 'H',              // Miax Pearl Exchange Llc Miax
    InternationalSecuritiesExchangeLlcIse = 'I', // International Securities Exchange Llc Ise
    CboeEdgaExchangeIncCboeEdga = 'J',           // Cboe Edga Exchange Inc Cboe Edga
    CboeEdgxExchangeIncCboeEdgx = 'K',           // Cboe Edgx Exchange Inc Cboe Edgx
    LongTermStockExchangeIncLtse = 'L',          // Long Term Stock Exchange Inc Ltse
    NyseTexasIncNyseTexas = 'M',                 // Nyse Texas Inc Nyse Texas
    NewYorkStockExchangeLlcNyse = 'N',           // New York Stock Exchange Llc Nyse
    NyseArcaIncNyseArca = 'P',                   // Nyse Arca Inc Nyse Arca
    ConsolidatedTapeSystemCts = 'S',             // Consolidated Tape System Cts
    NasdaqStockMarketLlcNasdaq = 'T',            // Nasdaq Stock Market Llc Nasdaq
    MembersExchangeLlcMemx = 'U',                // Members Exchange Llc Memx
    InvestorsExchangeLlcIex = 'V',               // Investors Exchange Llc Iex
    CboeStockExchangeIncCbsx = 'W',              // Cboe Stock Exchange Inc Cbsx
    NasdaqOmxPsxIncNasdaqOmxPsx = 'X',           // Nasdaq Omx Psx Inc Nasdaq Omx Psx
    CboeByxExchangeIncCboeByx = 'Y',             // Cboe Byx Exchange Inc Cboe Byx
    CboeBzxExchangeIncCboeBzx = 'Z',             // Cboe Bzx Exchange Inc Cboe Bzx
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ParticipantId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ParticipantId value);

} // namespace siac::cts::output::cta::v2_11_b
