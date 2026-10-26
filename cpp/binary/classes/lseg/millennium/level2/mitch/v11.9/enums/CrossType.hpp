#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// The type of the Cross/BTF Order.
enum class CrossType : std::uint8_t {
    InternalCross = 5,  // Internal Cross
    InternalBtf = 6,    // Internal Btf
    CommittedCross = 7, // Committed Cross
    CommittedBtf = 8,   // Committed Btf
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace lseg::millennium::level2::mitch::v11_9
