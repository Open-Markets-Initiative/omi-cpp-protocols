#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class MassMarketCondition : std::uint8_t {
    Normal = 0,   // Normal
    Stressed = 1, // Stressed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MassMarketCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MassMarketCondition value);

} // namespace eurex::t7::eobi::fbe::v13_0
