#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// O=Start of Messages, C=End of Messages
enum class EventCode : char {
    StartOfMessages = 'O', // Start Of Messages
    EndOfMessages = 'C',   // End Of Messages
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EventCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EventCode value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
