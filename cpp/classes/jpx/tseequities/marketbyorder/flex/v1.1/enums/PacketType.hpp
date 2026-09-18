#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// First byte of the Tcp packet identifying the packet type used as dispatch key
enum class PacketType : char {
    LoginRequestMessage = 'R',    // Login Request Message
    LoginResultMessage = 'A',     // Login Result Message
    MessageResponseMessage = 'S', // Message Response Message
    EndOfMessageMessage = 'G',    // End Of Message Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PacketType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PacketType value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
