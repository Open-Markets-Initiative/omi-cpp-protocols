#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies the Participant or Processor that generated the message
enum class ParticipantId : char {
    NyseAmerican = 'A', // Nyse American
    NasdaqOmxBx = 'B',  // Nasdaq Omx Bx
    NyseNational = 'C', // Nyse National
    FinraAdf = 'D',     // Finra Adf
    N24x = 'G',         // N24X
    Miax = 'H',         // Miax
    Ise = 'I',          // Ise
    CboeEdga = 'J',     // Cboe Edga
    CboeEdgx = 'K',     // Cboe Edgx
    Ltse = 'L',         // Ltse
    NyseTexas = 'M',    // Nyse Texas
    Nyse = 'N',         // Nyse
    NyseArca = 'P',     // Nyse Arca
    Cqs = 'S',          // Cqs
    Nasdaq = 'T',       // Nasdaq
    Memx = 'U',         // Memx
    Iex = 'V',          // Iex
    Cbsx = 'W',         // Cbsx
    NasdaqOmxPsx = 'X', // Nasdaq Omx Psx
    CboeByx = 'Y',      // Cboe Byx
    CboeBzx = 'Z',      // Cboe Bzx
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ParticipantId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ParticipantId value);

} // namespace siac::cqs::output::cta::v2_10_a
