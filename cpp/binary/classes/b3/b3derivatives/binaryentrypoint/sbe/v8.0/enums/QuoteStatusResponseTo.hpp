#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// quoteStatusResponseTo
enum class QuoteStatusResponseTo : char {
    Quote = '0',              // Quote
    QuoteRequest = '1',       // Quote Request
    QuoteCancel = '2',        // Quote Cancel
    QuoteRequestReject = '3', // Quote Request Reject
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(QuoteStatusResponseTo value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, QuoteStatusResponseTo value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
