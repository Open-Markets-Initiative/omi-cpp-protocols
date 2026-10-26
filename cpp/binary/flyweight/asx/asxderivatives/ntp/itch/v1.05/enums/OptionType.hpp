#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Indicates the type of option
enum class OptionType : char {
    Put = 'P',  // Put
    Call = 'C', // Call
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OptionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OptionType value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
