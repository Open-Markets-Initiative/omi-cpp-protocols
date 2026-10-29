#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

enum class MdControlType : std::uint8_t {
    StartOfSummary = 0,    // Start Of Summary
    EndOfSummary = 1,      // End Of Summary
    StartOfSettlement = 2, // Start Of Settlement
    EndOfSettlement = 3,   // End Of Settlement
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdControlType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdControlType value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
