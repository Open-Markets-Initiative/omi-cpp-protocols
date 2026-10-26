#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class MultiLegPriceModel : std::uint8_t {
    Standard = 0,    // Standard
    UserDefined = 1, // User Defined
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MultiLegPriceModel value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MultiLegPriceModel value);

} // namespace eurex::t7::eobi::fbe::v13_0
