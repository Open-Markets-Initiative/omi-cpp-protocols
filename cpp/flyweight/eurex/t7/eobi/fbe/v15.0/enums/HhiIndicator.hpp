#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class HhiIndicator : std::int8_t {
    NoUpdate = -1, // No Update
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(HhiIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, HhiIndicator value);

} // namespace eurex::t7::eobi::fbe::v15_0
