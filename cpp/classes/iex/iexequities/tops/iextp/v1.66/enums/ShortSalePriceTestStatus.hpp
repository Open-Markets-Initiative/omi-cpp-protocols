#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::tops::iextp::v1_66 {

// Reg. SHO short sale price test restriction status
enum class ShortSalePriceTestStatus : std::uint8_t {
    NotInEffect = 0, // Not In Effect
    InEffect = 1,    // In Effect
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ShortSalePriceTestStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ShortSalePriceTestStatus value);

} // namespace iex::iexequities::tops::iextp::v1_66
