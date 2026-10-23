#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class MultiLegReportingType : std::uint8_t {
    SingleSecurity = 1,                   // Single Security
    IndividualLegOfAMultiLegSecurity = 2, // Individual Leg Of A Multi Leg Security
    MultiLegSecurity = 3,                 // Multi Leg Security
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MultiLegReportingType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MultiLegReportingType value);

} // namespace eurex::t7::eobi::fbe::v15_0
