#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// Indicates an Imbalance Freeze for the auction.
enum class FreezeStatus : std::uint8_t {
    ImbalanceFreezeNotInEffect = 0, // Imbalance Freeze Not In Effect
    ImbalanceFreezeIsInEffect = 1,  // Imbalance Freeze Is In Effect
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FreezeStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FreezeStatus value);

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
