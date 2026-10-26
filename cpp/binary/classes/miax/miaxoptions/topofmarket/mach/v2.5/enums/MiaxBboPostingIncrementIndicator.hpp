#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// This is the Minimum Price Variation as agreed to by the Options industry (penny pilot
// program) and as published by MIAX
enum class MiaxBboPostingIncrementIndicator : char {
    Penny = 'P',         // Penny
    PennyOrNickel = 'N', // Penny Or Nickel
    NickelOrDime = 'D',  // Nickel Or Dime
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MiaxBboPostingIncrementIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MiaxBboPostingIncrementIndicator value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
