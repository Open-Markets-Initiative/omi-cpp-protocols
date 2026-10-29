#pragma once

#include "../types/LastTimestamp.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// The End of Session message is sent for each unit when the unit shuts down
struct EndOfSession {

    LastTimestamp last_timestamp;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x2D;

    // parse method
    static EndOfSession* parse(std::byte* buffer) {
        return reinterpret_cast<EndOfSession*>(buffer);
    }

    // parse method const
    static const EndOfSession* parse(const std::byte* buffer) {
        return reinterpret_cast<const EndOfSession*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EndOfSession* parse(const MessageHeader* header) {
        return reinterpret_cast<const EndOfSession*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
