// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/Currency.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The Currency Associated With A Reported Price
enum class Currency : char {
    Usd = 'U', // Usd
    Cad = 'C', // Cad
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Currency value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Currency value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
