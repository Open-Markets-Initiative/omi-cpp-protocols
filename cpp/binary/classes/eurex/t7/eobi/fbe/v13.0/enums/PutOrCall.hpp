#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class PutOrCall : std::uint8_t {
    Put = 0,  // Put
    Call = 1, // Call
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PutOrCall value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PutOrCall value);

} // namespace eurex::t7::eobi::fbe::v13_0
