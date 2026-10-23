#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// 0x00 for regular trading session
enum class SessionIndicator : std::uint8_t {
    Regular = 0,    // Regular
    PreMarket = 88, // Pre Market
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SessionIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SessionIndicator value);

} // namespace siac::opra::output::obi::v6_2
