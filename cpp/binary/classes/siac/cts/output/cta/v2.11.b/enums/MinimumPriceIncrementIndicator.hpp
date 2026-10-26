#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the applicable tick size for a symbol
enum class MinimumPriceIncrementIndicator : char {
    PennyMpi001 = '1',      // Penny Mpi 0.01
    HalfPennyMpi0005 = '2', // Half Penny Mpi 0.005
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MinimumPriceIncrementIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MinimumPriceIncrementIndicator value);

} // namespace siac::cts::output::cta::v2_11_b
