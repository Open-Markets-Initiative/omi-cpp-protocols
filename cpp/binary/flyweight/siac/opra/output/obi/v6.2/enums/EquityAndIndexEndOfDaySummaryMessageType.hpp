#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Equity and Index End of Day Summary Message Type
enum class EquityAndIndexEndOfDaySummaryMessageType : char {
    EquityAndIndexEndOfDaySummary = ' ', // Equity And Index End Of Day Summary
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EquityAndIndexEndOfDaySummaryMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EquityAndIndexEndOfDaySummaryMessageType value);

} // namespace siac::opra::output::obi::v6_2
