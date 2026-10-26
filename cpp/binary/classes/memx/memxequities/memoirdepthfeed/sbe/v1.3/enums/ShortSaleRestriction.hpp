#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// ShortSaleRestriction
enum class ShortSaleRestriction : std::uint8_t {
    False = 0, // False
    True = 1,  // True
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ShortSaleRestriction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ShortSaleRestriction value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
