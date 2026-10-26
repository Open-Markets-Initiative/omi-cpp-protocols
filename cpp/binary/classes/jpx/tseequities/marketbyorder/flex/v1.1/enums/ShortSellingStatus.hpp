#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates application of the Short Selling Regulation
enum class ShortSellingStatus : std::uint8_t {
    ShortSellingRegulationIsNotApplied = 0, // Short Selling Regulation Is Not Applied
    ShortSellingRegulationIsApplied = 1,    // Short Selling Regulation Is Applied
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ShortSellingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ShortSellingStatus value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
