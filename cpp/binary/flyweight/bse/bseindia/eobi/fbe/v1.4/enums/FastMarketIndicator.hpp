#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Indicates if product is in the state Fast Market.
enum class FastMarketIndicator : std::uint8_t {
    No = 0,  // No
    Yes = 1, // Yes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FastMarketIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FastMarketIndicator value);

} // namespace bse::bseindia::eobi::fbe::v1_4
