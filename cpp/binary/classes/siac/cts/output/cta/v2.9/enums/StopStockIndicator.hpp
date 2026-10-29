#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_9 {

// The transaction that constituted the trade-through was the execution by a trading center of
// an order for which, at the time of receipt of the order, the trading center had guaranteed
// an execution at no worse than a specified price
enum class StopStockIndicator : char {
    NotApplicable = '0', // Not Applicable
    StopStock = '1',     // Stop Stock
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StopStockIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StopStockIndicator value);

} // namespace siac::cts::output::cta::v2_9
