#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// The currency in which all Futures Instruments of the Futures Product will trade
enum class Currency : char {
    Usd = 'U', // Usd
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Currency value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Currency value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
