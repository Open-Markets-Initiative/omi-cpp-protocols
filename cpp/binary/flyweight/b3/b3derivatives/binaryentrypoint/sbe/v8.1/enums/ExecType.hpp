#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// execType
enum class ExecType : char {
    Trade = 'F',       // Trade
    TradeCancel = 'H', // Trade Cancel
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExecType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExecType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
