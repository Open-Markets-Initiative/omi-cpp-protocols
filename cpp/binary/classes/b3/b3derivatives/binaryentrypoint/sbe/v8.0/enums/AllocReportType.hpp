#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// allocReportType
enum class AllocReportType : char {
    RequestToIntermediary = '8', // Request To Intermediary
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AllocReportType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AllocReportType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
