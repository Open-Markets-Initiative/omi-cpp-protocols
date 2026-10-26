#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Lot Type
enum class LotType : std::uint8_t {
    Undefined = 0,    // Undefined
    OddLot = 1,       // Odd Lot
    RoundLot = 2,     // Round Lot
    BlockLot = 3,     // Block Lot
    AllOrNoneLot = 4, // All Or None Lot
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LotType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LotType value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
