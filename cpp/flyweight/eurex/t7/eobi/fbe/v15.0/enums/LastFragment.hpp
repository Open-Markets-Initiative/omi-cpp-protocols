#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class LastFragment : std::uint8_t {
    N = 0, // N
    Y = 1, // Y
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LastFragment value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LastFragment value);

} // namespace eurex::t7::eobi::fbe::v15_0
