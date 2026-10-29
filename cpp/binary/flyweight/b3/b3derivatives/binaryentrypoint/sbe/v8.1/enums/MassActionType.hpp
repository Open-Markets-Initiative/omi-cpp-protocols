#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// massActionType
enum class MassActionType : std::uint8_t {
    ReleaseOrdersFromSuspension = 2, // Release Orders From Suspension
    CancelOrders = 3,                // Cancel Orders
    CancelAndSuspendOrders = 4,      // Cancel And Suspend Orders
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MassActionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MassActionType value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
