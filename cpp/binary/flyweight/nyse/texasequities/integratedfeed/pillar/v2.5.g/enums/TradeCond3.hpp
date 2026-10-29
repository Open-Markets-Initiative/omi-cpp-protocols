#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// Extended hours/sequencing related conditions.
enum class TradeCond3 : char {
    Na = ' ',                             // Na
    ExtendedHoursTrade = 'T',             // Extended Hours Trade
    ExtendedHoursSoldOutOfSequence = 'U', // Extended Hours Sold Out Of Sequence
    Sold = 'Z',                           // Sold
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCond3 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCond3 value);

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
