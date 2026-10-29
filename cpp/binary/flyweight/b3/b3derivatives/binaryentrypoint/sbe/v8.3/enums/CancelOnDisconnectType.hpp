#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// cancelOnDisconnectType
enum class CancelOnDisconnectType : std::uint8_t {
    DoNotCancelOnDisconnectOrTerminate = 0, // Do Not Cancel On Disconnect Or Terminate
    CancelOnDisconnectOnly = 1,             // Cancel On Disconnect Only
    CancelOnTerminateOnly = 2,              // Cancel On Terminate Only
    CancelOnDisconnectOrTerminate = 3,      // Cancel On Disconnect Or Terminate
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CancelOnDisconnectType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CancelOnDisconnectType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
