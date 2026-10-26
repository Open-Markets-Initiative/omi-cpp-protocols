#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Identifies the applicable Nasdaq market center
enum class MarketCode : char {
    Nasdaq = 'Q',      // Nasdaq
    NasdaqTexas = 'B', // Nasdaq Texas
    Psx = 'X',         // Psx
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketCode value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
