#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Option or Equity instrument
enum class LegSecurityType : char {
    Option = 'O', // Option
    Equity = 'E', // Equity
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSecurityType value);

} // namespace cboe::c1options::complex::pitch::v2_1_18
