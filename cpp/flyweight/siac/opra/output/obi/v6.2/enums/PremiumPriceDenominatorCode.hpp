#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Represents the first price paid for an option during the trading day.
enum class PremiumPriceDenominatorCode : char {
    Ten = 'A',             // Ten
    Hundred = 'B',         // Hundred
    Thousand = 'C',        // Thousand
    TenThousand = 'D',     // Ten Thousand
    HundredThousand = 'E', // Hundred Thousand
    Million = 'F',         // Million
    TenMillion = 'G',      // Ten Million
    NoFraction = 'I',      // No Fraction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PremiumPriceDenominatorCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PremiumPriceDenominatorCode value);

} // namespace siac::opra::output::obi::v6_2
