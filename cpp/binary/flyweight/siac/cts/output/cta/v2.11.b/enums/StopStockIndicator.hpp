#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies whether the transaction constituted a stopped order
enum class StopStockIndicator : char {
    StopStockNotApplicable = '0', // Stop Stock Not Applicable
    StopStock = '1',              // Stop Stock
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StopStockIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StopStockIndicator value);

} // namespace siac::cts::output::cta::v2_11_b
