#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// lotType
enum class LotType : std::uint8_t {
    OddLot = 1,   // Odd Lot
    RoundLot = 2, // Round Lot
    BlockLot = 3, // Block Lot
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LotType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LotType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_9
