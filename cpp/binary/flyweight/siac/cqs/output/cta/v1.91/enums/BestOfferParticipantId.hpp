#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Identifies the Participant that submitted the Best Bid on a consolidated basis.
enum class BestOfferParticipantId : char {
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
    Cqs = 'S',          // Cqs
    Nasdaq = 'T',       // Nasdaq
    Iex = 'V',          // Iex
    Cbsx = 'W',         // Cbsx
    NasdaqPsx = 'X',    // Nasdaq Psx
    CboeByx = 'Y',      // Cboe Byx
    CboeBzx = 'Z',      // Cboe Bzx
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BestOfferParticipantId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BestOfferParticipantId value);

} // namespace siac::cqs::output::cta::v1_91
