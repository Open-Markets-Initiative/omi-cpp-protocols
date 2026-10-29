#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

// Reflects the current eligibility for auto execution of the options security in the options
// market.
enum class OpenState : char {
    OpenForAutoExecution = 'Y',   // Open For Auto Execution
    ClosedForAutoExecution = 'N', // Closed For Auto Execution
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpenState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpenState value);

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
