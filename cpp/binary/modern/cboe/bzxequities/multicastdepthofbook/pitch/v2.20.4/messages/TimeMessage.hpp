#pragma once

#include "../types/Time.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Time message
struct TimeMessage {

    Time time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x20;

    // parse method
    static TimeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TimeMessage*>(buffer);
    }

    // parse method const
    static const TimeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TimeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TimeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TimeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
