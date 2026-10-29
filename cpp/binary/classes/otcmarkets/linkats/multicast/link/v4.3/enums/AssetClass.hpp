#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Asset class indicator.
enum class AssetClass : std::uint8_t {
    Equity = 1,      // Equity
    FixedIncome = 2, // Fixed Income
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AssetClass value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AssetClass value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
