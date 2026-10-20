#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates the start or end of communication
enum class CommunicationStartEndFlag : std::uint8_t {
    HealthCheckControl = 0, // Health Check Control
    CommunicationStart = 1, // Communication Start
    CommunicationEnd = 2,   // Communication End
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CommunicationStartEndFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CommunicationStartEndFlag value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
