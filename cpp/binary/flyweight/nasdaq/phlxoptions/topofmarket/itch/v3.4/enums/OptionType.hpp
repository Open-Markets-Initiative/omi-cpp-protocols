#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Option Type value
enum class OptionType : char {
    Call = 'C', // Call
    Put = 'P',  // Put
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OptionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OptionType value);

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
