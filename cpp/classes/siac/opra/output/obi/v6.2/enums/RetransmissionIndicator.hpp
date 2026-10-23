#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::opra::output::obi::v6_2 {

// Contains either a space; not a retransmitted message or V; indicating a retransmission of
// the block.
enum class RetransmissionIndicator : char {
    NotRetransmitted = ' ', // Not Retransmitted
    Retransmitted = 'V',    // Retransmitted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetransmissionIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetransmissionIndicator value);

} // namespace siac::opra::output::obi::v6_2
