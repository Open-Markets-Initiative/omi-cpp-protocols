#pragma once

#include "../types/Timestamp.hpp"
#include "../types/EventCode.hpp"
#include "../types/SourceVenue.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

#pragma pack(push, 1)

// Sent to indicate the start and end of the day.
struct SystemEventMessage {

    Timestamp timestamp;
    EventCode event_code;
    SourceVenue source_venue;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x53;

    // parse method
    static SystemEventMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SystemEventMessage*>(buffer);
    }

    // parse method const
    static const SystemEventMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SystemEventMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SystemEventMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SystemEventMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
