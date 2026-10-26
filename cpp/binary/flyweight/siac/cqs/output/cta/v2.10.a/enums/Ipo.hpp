#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies whether the security symbol is an IPO
enum class Ipo : char {
    NotAnIpoSymbol = '0', // Not An Ipo Symbol
    IpoSymbol = '1',      // Ipo Symbol
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Ipo value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Ipo value);

} // namespace siac::cqs::output::cta::v2_10_a
