#pragma once

#include "../types/Timestamp.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// End of Session message
struct EndOfSessionMessage {

    Timestamp timestamp;

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
