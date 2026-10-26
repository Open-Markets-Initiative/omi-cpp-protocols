#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deep::iextp::v1_08 {

// Side of the unpaired shares at the Reference Price using orders on the Auction Book
enum class ImbalanceSide : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
    None = 'N', // None
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImbalanceSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImbalanceSide value);

} // namespace iex::iexequities::deep::iextp::v1_08
