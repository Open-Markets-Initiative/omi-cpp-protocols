#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the Limit Up Limit Down tier of the security symbol
enum class LuldTier : char {
    LuldNotApplicable = '0', // Luld Not Applicable
    LuldTier1Security = '1', // Luld Tier 1 Security
    LuldTier2Security = '2', // Luld Tier 2 Security
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LuldTier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LuldTier value);

} // namespace siac::cts::output::cta::v2_11_b
