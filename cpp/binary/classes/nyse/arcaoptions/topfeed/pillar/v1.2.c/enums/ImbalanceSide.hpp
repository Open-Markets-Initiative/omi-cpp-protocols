#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The side of the TotalImbalanceQty
enum class ImbalanceSide : char {
    Buy = 'B',         // Buy
    Sell = 'S',        // Sell
    NoImbalance = ' ', // No Imbalance
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImbalanceSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImbalanceSide value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
