#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Administrative message type
enum class AdministrativeMessageType : char {
    AdministrativeUnformattedMessage = 'H', // Administrative Unformatted Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AdministrativeMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AdministrativeMessageType value);

} // namespace siac::cqs::output::cta::v1_91
