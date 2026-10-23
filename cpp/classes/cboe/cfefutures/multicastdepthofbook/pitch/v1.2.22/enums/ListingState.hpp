#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Listing State Values
enum class ListingState : char {
    Active = 'A',   // Active
    Inactive = 'I', // Inactive
    Test = 'T',     // Test
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ListingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ListingState value);

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
