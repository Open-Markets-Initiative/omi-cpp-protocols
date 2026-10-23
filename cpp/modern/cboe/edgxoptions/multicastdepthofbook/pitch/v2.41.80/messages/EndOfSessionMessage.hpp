#pragma once

#include "../types/TimeOffset.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

#pragma pack(push, 1)

// The End of Session message is sent for each unit when the unit shuts down. No more sequenced messages will be delivered for this unit, but heartbeats from the unit may be received.
struct EndOfSessionMessage {

    TimeOffset time_offset;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x2D;

    // parse method
    static EndOfSessionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfSessionMessage*>(buffer);
    }

    // parse method const
    static const EndOfSessionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfSessionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfSessionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const EndOfSessionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
