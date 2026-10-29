#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// quoteStatus
enum class QuoteStatus : std::uint8_t {
    Expired = 7,       // Expired
    Accepted = 0,      // Accepted
    Rejected = 5,      // Rejected
    QuoteNotFound = 9, // Quote Not Found
    Pending = 10,      // Pending
    Pass = 11,         // Pass
    Canceled = 17,     // Canceled
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteStatus value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
