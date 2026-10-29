#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// ‘F’ = Futures
enum class InstrumentType : char {
    Futures = 'F', // Futures
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InstrumentType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InstrumentType value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
