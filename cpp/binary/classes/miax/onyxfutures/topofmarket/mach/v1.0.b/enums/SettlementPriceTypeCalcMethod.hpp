#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Actual or Theoretical Settlement Price Indicator
enum class SettlementPriceTypeCalcMethod : char {
    Actual = 'A',      // Actual
    Theoretical = 'T', // Theoretical
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlementPriceTypeCalcMethod value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlementPriceTypeCalcMethod value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
