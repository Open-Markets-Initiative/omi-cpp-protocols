#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// multiLegReportingType
enum class MultiLegReportingType : char {
    SingleSecurity = '1',                  // Single Security
    IndividuallegOfMultilegSecurity = '2', // Individualleg Of Multileg Security
    MultilegSecurity = '3',                // Multileg Security
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MultiLegReportingType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MultiLegReportingType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
