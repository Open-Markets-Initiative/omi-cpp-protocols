#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Start or end of day event code.
enum class EventCode : char {
    EndOfDay = 'C',   // End Of Day
    StartOfDay = 'O', // Start Of Day
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventCode value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
