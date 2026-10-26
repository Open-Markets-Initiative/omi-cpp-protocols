#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// ASCII character that identifies the Participant or Processor that initiated the message.
enum class ParticipantId : char {
    Amex = 'A',    // Amex
    Box = 'B',     // Box
    Cboe = 'C',    // Cboe
    Emerald = 'D', // Emerald
    Edgx = 'E',    // Edgx
    Gemx = 'H',    // Gemx
    Ise = 'I',     // Ise
    Mrx = 'J',     // Mrx
    Miax = 'M',    // Miax
    Nyse = 'N',    // Nyse
    Opra = 'O',    // Opra
    Pearl = 'P',   // Pearl
    Nasd = 'Q',    // Nasd
    Sphr = 'S',    // Sphr
    Bx = 'T',      // Bx
    Memx = 'U',    // Memx
    C2 = 'W',      // C 2
    Phlx = 'X',    // Phlx
    Bats = 'Z',    // Bats
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ParticipantId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ParticipantId value);

} // namespace siac::opra::output::obi::v6_2
