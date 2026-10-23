#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// The Underlying Price Denominator Code field indicates the position of the floating decimal
// point within the Underlying Price field.
enum class UnderlyingPriceDenominatorCode : char {
    Ten = 'A',             // Ten
    Hundred = 'B',         // Hundred
    Thousand = 'C',        // Thousand
    TenThousand = 'D',     // Ten Thousand
    HundredThousand = 'E', // Hundred Thousand
    Million = 'F',         // Million
    TenMillion = 'G',      // Ten Million
    HundredMillion = 'H',  // Hundred Million
    NoFraction = 'I',      // No Fraction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnderlyingPriceDenominatorCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnderlyingPriceDenominatorCode value);

} // namespace siac::opra::output::obi::v6_2
