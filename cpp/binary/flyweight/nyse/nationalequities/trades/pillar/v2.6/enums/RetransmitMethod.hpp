#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// The delivery method for the requested symbol index mapping information. Valid values: 0 -
// deliver via UDP.
enum class RetransmitMethod : std::uint8_t {
    DeliverViaUdp = 0, // Deliver Via Udp
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetransmitMethod value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetransmitMethod value);

} // namespace nyse::nationalequities::trades::pillar::v2_6
