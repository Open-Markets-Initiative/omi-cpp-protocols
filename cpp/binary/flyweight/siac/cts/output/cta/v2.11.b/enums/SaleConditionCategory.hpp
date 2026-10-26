#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// In the Short Trade format, identifies the Sale Condition Category level associated with a
// trade
enum class SaleConditionCategory : char {
    SaleConditionCategoryNotApplicable = ' ', // Sale Condition Category Not Applicable
    SaleConditionCategory1 = '1',             // Sale Condition Category 1
    SaleConditionCategory2 = '2',             // Sale Condition Category 2
    SaleConditionCategory3 = '3',             // Sale Condition Category 3
    SaleConditionCategory4 = '4',             // Sale Condition Category 4
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SaleConditionCategory value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SaleConditionCategory value);

} // namespace siac::cts::output::cta::v2_11_b
