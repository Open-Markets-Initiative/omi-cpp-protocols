#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::tops::iextp::v1_66 {

// Indicates which Limit Up-Limit Down price band calculation parameter is to be used
enum class LuldTier : std::uint8_t {
    NotApplicable = 0, // Not Applicable
    Tier1NmsStock = 1, // Tier 1 Nms Stock
    Tier2NmsStock = 2, // Tier 2 Nms Stock
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LuldTier value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LuldTier value);

} // namespace iex::iexequities::tops::iextp::v1_66
