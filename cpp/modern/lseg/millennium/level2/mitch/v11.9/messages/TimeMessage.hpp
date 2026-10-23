#pragma once

#include "../types/Seconds.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Sent by the server for every second for which at least one application message is generated.
struct TimeMessage {

    Seconds seconds;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x54;

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
