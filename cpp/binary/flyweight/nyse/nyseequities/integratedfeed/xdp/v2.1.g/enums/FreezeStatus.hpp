#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// Freeze status code
enum class FreezeStatus : std::uint8_t {
    NoImbalanceFreeze = 0, // No Imbalance Freeze
    ImbalanceFreeze = 1,   // Imbalance Freeze
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FreezeStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FreezeStatus value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
