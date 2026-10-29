#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// Freeze status
enum class FreezeStatus : std::uint8_t {
    NoImbalanceFreeze = 0, // No Imbalance Freeze
    ImbalanceFreeze = 1,   // Imbalance Freeze
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FreezeStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FreezeStatus value);

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
