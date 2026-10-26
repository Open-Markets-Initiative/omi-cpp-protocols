#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deepplus::iextp::v1_01 {

// Side of order
enum class Side : char {
    Buy = '8',  // Buy
    Sell = '5', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Side value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Side value);

} // namespace iex::iexequities::deepplus::iextp::v1_01
