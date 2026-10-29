#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

// The delivery method for the requested symbol index mapping information.
enum class RetransmitMethod : std::uint8_t {
    Udp = 0, // Udp
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetransmitMethod value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetransmitMethod value);

} // namespace nyse::arcaequities::bbo::xdp::v2_4_c
