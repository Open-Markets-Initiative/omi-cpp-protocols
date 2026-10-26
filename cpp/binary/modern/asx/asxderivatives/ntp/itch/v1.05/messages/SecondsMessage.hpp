#pragma once

#include "../types/Second.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// A ‘seconds’ Nanoseconds is issued every second and any message thereafter will be stamped with the number of nanoseconds past the last Time message received as a time reference point
struct SecondsMessage {

    Second second;

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
