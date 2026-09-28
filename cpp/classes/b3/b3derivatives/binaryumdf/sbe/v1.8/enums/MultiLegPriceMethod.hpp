#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// multiLegPriceMethod
enum class MultiLegPriceMethod : std::uint8_t {
    NetPrice = 0,                     // Net Price
    ReversedNetPrice = 1,             // Reversed Net Price
    YieldDifference = 2,              // Yield Difference
    Individual = 3,                   // Individual
    ContractWeightedAveragePrice = 4, // Contract Weighted Average Price
    MultipliedPrice = 5,              // Multiplied Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MultiLegPriceMethod value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MultiLegPriceMethod value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
