#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SystemEvent.hpp"
#include "../messages/SequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// A System Event Message signals a Japannext PTS system-wide event
struct SystemEventMessage {

    Timestamp timestamp;
    SystemEvent system_event;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'S';

    // parse method
    static SystemEventMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SystemEventMessage*>(buffer);
    }

    // parse method const
    static const SystemEventMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SystemEventMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SystemEventMessage* parse(const SequencedDataPacket* header) {
        return reinterpret_cast<const SystemEventMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(SequencedDataPacket));
    }
};

#pragma pack(pop)
}
