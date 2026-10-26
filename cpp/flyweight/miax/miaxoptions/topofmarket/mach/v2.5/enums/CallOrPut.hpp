#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Option Type
enum class CallOrPut : char {
    Call = 'C', // Call
    Put = 'P',  // Put
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CallOrPut value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CallOrPut value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
