#pragma once

#include "../types/EventCode.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

// System Event Messages is used to signal key market or data feed control events.
struct SystemEventMessage {

    EventCode event_code;

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
