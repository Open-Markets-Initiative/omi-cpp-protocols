#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Denotes if an issue or quoting participant record is set-up in NASDAQ systems in a
// live/production, test, or demo state
enum class Authenticity : char {
    LiveProduction = 'P', // Live Production
    Test = 'T',           // Test
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Authenticity value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Authenticity value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
