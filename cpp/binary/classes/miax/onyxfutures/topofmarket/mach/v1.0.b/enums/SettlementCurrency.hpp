#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// The Currency in which the Product settles
enum class SettlementCurrency : char {
    Usd = 'U', // Usd
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlementCurrency value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlementCurrency value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
