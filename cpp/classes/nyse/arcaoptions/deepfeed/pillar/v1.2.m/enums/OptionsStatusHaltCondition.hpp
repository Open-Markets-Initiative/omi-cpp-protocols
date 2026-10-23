#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Halt condition for option series.
enum class OptionsStatusHaltCondition : char {
    SeriesNotDelayedhalted = '~', // Series Not Delayedhalted
    OptionSeriesIsHalted = 'h',   // Option Series Is Halted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OptionsStatusHaltCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OptionsStatusHaltCondition value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
