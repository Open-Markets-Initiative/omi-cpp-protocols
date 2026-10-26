#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Side of the leg
enum class SideLeg : char {
    Buy = 'B',        // Buy
    Sell = 'S',       // Sell
    NotDefined = ' ', // Not Defined
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SideLeg value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SideLeg value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
