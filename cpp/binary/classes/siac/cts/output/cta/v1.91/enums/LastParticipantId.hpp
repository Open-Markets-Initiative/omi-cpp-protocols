#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v1_91 {

// Refer to Participant ID field description for Participant codes
enum class LastParticipantId : char {
    NyseAmerican = 'A', // Nyse American
    NasdaqBx = 'B',     // Nasdaq Bx
    NyseNational = 'C', // Nyse National
    FinraAdf = 'D',     // Finra Adf
    Ise = 'I',          // Ise
    CboeEdga = 'J',     // Cboe Edga
    CboeEdgx = 'K',     // Cboe Edgx
    Ltse = 'L',         // Ltse
    NyseChicago = 'M',  // Nyse Chicago
    Nyse = 'N',         // Nyse
    NyseArca = 'P',     // Nyse Arca
    Cts = 'S',          // Cts
    Nasdaq = 'T',       // Nasdaq
    Iex = 'V',          // Iex
    Cbsx = 'W',         // Cbsx
    NasdaqPsx = 'X',    // Nasdaq Psx
    CboeByx = 'Y',      // Cboe Byx
    CboeBzx = 'Z',      // Cboe Bzx
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LastParticipantId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LastParticipantId value);

} // namespace siac::cts::output::cta::v1_91
