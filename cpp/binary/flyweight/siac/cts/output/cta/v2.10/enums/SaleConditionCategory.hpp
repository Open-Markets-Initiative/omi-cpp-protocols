#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Identifies the Sale Condition Category level associated with a trade
enum class SaleConditionCategory : char {
    NotApplicable = ' ', // Not Applicable
    Category1 = '1',     // Category 1
    Category2 = '2',     // Category 2
    Category3 = '3',     // Category 3
    Category4 = '4',     // Category 4
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SaleConditionCategory value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SaleConditionCategory value);

} // namespace siac::cts::output::cta::v2_10
