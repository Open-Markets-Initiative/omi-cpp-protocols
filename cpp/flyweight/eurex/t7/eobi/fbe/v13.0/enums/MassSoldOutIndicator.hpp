#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class MassSoldOutIndicator : std::uint8_t {
    SoldOut = 1, // Sold Out
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MassSoldOutIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MassSoldOutIndicator value);

} // namespace eurex::t7::eobi::fbe::v13_0
