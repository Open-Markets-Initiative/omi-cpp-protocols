#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Indicates whether the Instrument ID has been assigned by the exchange or from an external
// industry source
enum class InstrumentIdSource : char {
    Exchange = 'E', // Exchange
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InstrumentIdSource value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InstrumentIdSource value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
