#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// 1=Call, 2=Put
enum class PutOrCall : std::uint8_t {
    Call = 1, // Call
    Put = 2,  // Put
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PutOrCall value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PutOrCall value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
