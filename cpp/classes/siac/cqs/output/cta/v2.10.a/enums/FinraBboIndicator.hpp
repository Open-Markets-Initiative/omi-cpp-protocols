#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// For FINRA ADF, represents the FINRA BBO state of the FINRA ADF quote
enum class FinraBboIndicator : char {
    FinraBboIndicatorNotApplicable = ' ', // Finra Bbo Indicator Not Applicable
    NoFinraBboChange = 'A',               // No Finra Bbo Change
    NoFinraBboExists = 'B',               // No Finra Bbo Exists
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FinraBboIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FinraBboIndicator value);

} // namespace siac::cqs::output::cta::v2_10_a
