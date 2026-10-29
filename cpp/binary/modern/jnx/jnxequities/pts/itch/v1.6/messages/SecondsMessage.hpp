#pragma once

#include "../types/Seconds.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

#pragma pack(push, 1)

// Reflects the number of seconds past midnight that the Timestamp message was generated.
struct SecondsMessage {

    Seconds seconds;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'T';

    // parse method
    static SecondsMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecondsMessage*>(buffer);
    }

    // parse method const
    static const SecondsMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecondsMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecondsMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecondsMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
