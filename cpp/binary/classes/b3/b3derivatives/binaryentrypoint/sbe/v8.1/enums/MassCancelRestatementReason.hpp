#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// execRestatementReason
enum class MassCancelRestatementReason : std::uint8_t {
    OrderMassActionFromClientRequest = 202,            // Order Mass Action From Client Request
    MassCancelOrderDueToOperationalErrorRequest = 207, // Mass Cancel Order Due To Operational Error Request
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MassCancelRestatementReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MassCancelRestatementReason value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
