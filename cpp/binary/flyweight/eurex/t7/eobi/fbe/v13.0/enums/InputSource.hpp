#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class InputSource : std::uint8_t {
    ClipClientBroker = 1, // Clip Client Broker
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InputSource value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InputSource value);

} // namespace eurex::t7::eobi::fbe::v13_0
