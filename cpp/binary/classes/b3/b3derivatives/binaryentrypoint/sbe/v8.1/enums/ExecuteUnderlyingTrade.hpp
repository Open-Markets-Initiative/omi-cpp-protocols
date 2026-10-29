#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// executeUnderlyingTrade
enum class ExecuteUnderlyingTrade : char {
    NoUnderlyingTrade = '0',       // No Underlying Trade
    UnderlyingOpposingTrade = '1', // Underlying Opposing Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ExecuteUnderlyingTrade value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ExecuteUnderlyingTrade value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
