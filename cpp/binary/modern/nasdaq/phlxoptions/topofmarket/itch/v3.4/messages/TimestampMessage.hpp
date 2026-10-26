#pragma once

#include "../types/Second.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The system event message type is used to signal a market or data feed handler event.
struct TimestampMessage {

    Second second;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'T';

    // parse method
    static TimestampMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TimestampMessage*>(buffer);
    }

    // parse method const
    static const TimestampMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TimestampMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TimestampMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TimestampMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
