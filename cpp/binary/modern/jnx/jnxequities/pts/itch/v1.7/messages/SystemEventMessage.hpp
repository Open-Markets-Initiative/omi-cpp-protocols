#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/Group.hpp"
#include "../types/SystemEvent.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

#pragma pack(push, 1)

// System Event Messages signal data feed, system and market events.
struct SystemEventMessage {

    Nanoseconds nanoseconds;
    Group group;
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
    static const SystemEventMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SystemEventMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
