#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Issue Values
enum class Issue : char {
    PeriodicIndicativeSettlement = 'i', // Periodic Indicative Settlement
    IndicativeSettlement = 'I',         // Indicative Settlement
    InitialSettlement = 'S',            // Initial Settlement
    ReissuedSettlement = 'R',           // Reissued Settlement
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Issue value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Issue value);

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
