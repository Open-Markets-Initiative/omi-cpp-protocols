#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v6_0 {

// End-of-event marker (0 = more to follow, 1 = last packet of event)
enum class CompletionIndicator : std::uint8_t {
    Incomplete = 0, // Incomplete
    Complete = 1,   // Complete
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CompletionIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CompletionIndicator value);

} // namespace eurex::t7::eobi::fbe::v6_0
