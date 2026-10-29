#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// Currently defaulted to 0.
enum class PositionChange : std::uint8_t {
    Kept = 0, // Kept
    Lost = 1, // Lost
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PositionChange value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PositionChange value);

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
