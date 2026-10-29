#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// “N” – New strategy created
enum class UpdateReason : char {
    NewStrategyCreated = 'N', // New Strategy Created
    Updated = 'U',            // Updated
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UpdateReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UpdateReason value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
