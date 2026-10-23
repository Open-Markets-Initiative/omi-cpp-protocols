#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Message Type
enum class MessageType : std::uint8_t {
    HeartbeatMessage = 0,       // Heartbeat Message
    SessionShutdownMessage = 1, // Session Shutdown Message
    SequencedMessage = 2,       // Sequenced Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
