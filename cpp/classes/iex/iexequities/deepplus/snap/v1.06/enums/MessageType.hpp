#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deepplus::snap::v1_06 {

// Code identifying this message type
enum class MessageType : char {
    SnapshotRequestMessage = 'r', // Snapshot Request Message
    ErrorResponseMessage = 'e',   // Error Response Message
    SnapshotStartMessage = 's',   // Snapshot Start Message
    SnapshotDataMessage = 'd',    // Snapshot Data Message
    SnapshotEndMessage = 'x',     // Snapshot End Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace iex::iexequities::deepplus::snap::v1_06
