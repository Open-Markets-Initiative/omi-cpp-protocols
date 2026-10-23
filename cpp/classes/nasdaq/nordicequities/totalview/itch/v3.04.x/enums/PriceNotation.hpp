#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Populated with M if price is monetary value
enum class PriceNotation : char {
    MonetaryValue = 'M', // Monetary Value
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceNotation value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceNotation value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
