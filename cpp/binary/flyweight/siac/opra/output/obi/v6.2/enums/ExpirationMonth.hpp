#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Indicates the expiration month and identifies the option as a Call or a Put.
enum class ExpirationMonth : char {
    JanuaryCall = 'A',   // January Call
    JanuaryPut = 'M',    // January Put
    FebruaryCall = 'B',  // February Call
    FebruaryPut = 'N',   // February Put
    MarchCall = 'C',     // March Call
    MarchPut = 'O',      // March Put
    AprilCall = 'D',     // April Call
    AprilPut = 'P',      // April Put
    MayCall = 'E',       // May Call
    MayPut = 'Q',        // May Put
    JuneCall = 'F',      // June Call
    JunePut = 'R',       // June Put
    JulyCall = 'G',      // July Call
    JulyPut = 'S',       // July Put
    AugustCall = 'H',    // August Call
    AugustPut = 'T',     // August Put
    SeptemberCall = 'I', // September Call
    SeptemberPut = 'U',  // September Put
    OctoberCall = 'J',   // October Call
    OctoberPut = 'V',    // October Put
    NovemberCall = 'K',  // November Call
    NovemberPut = 'W',   // November Put
    DecemberCall = 'L',  // December Call
    DecemberPut = 'X',   // December Put
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExpirationMonth value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExpirationMonth value);

} // namespace siac::opra::output::obi::v6_2
