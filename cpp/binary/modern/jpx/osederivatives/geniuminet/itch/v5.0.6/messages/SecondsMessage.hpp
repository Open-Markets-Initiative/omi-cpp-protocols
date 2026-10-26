#pragma once

#include "../types/Seconds.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Sent every second for which at least one ITCH message is being generated
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
