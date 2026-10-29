#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Volume Types
enum class MdVolumeType : std::uint8_t {
    TotalLimit = 0,                   // Total Limit
    CustomerLimit = 1,                // Customer Limit
    TotalContingencyAllOrNone = 2,    // Total Contingency All Or None
    CustomerContingencyAllOrNone = 3, // Customer Contingency All Or None
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdVolumeType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdVolumeType value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
