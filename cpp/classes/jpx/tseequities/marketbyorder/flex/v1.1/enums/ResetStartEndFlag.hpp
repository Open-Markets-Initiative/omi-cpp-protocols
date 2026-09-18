#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// When TSE needs to reset all distributed data, this indicates the start or end of the process
enum class ResetStartEndFlag : std::uint8_t {
    StartOfResetDissemination = 1, // Start Of Reset Dissemination
    EndOfResetDissemination = 2,   // End Of Reset Dissemination
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ResetStartEndFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ResetStartEndFlag value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
