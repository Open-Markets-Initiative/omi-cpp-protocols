#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class SettlMethod : std::uint8_t {
    Cash = 0,     // Cash
    Physical = 1, // Physical
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlMethod value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlMethod value);

} // namespace eurex::t7::eobi::fbe::v13_0
