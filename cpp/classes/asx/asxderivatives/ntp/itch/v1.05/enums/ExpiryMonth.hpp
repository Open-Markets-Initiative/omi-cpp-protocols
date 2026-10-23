#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Month of expiry for futures contract types, zero otherwise.
enum class ExpiryMonth : std::uint8_t {
    Jan = 1,  // Jan
    Feb = 2,  // Feb
    Mar = 3,  // Mar
    Apr = 4,  // Apr
    May = 5,  // May
    Jun = 6,  // Jun
    Jul = 7,  // Jul
    Aug = 8,  // Aug
    Sep = 9,  // Sep
    Oct = 10, // Oct
    Nov = 11, // Nov
    Dec = 12, // Dec
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExpiryMonth value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExpiryMonth value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
