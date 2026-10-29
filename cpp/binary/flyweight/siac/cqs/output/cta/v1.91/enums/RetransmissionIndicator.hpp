#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Indicates an original message or a retransmitted block
enum class RetransmissionIndicator : char {
    Original = 'O',      // Original
    Retransmitted = 'V', // Retransmitted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetransmissionIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetransmissionIndicator value);

} // namespace siac::cqs::output::cta::v1_91
