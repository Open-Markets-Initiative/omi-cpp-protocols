#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Option Type: “C” = Call, “P” = Put
enum class CallOrPut : char {
    Call = 'C', // Call
    Put = 'P',  // Put
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CallOrPut value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CallOrPut value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
