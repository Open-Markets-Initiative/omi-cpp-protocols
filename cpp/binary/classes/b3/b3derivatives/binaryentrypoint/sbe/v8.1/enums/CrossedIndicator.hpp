#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// crossedIndicator
enum class CrossedIndicator : std::uint16_t {
    StructuredTransaction = 1001, // Structured Transaction
    OperationalError = 1002,      // Operational Error
    TwapVwap = 1003,              // Twap Vwap
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossedIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossedIndicator value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
