#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/EventCode.hpp"
#include "../types/Version.hpp"
#include "../types/Subversion.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

#pragma pack(push, 1)

// The system event message type is used to signal a market or data feed handler event.
struct SystemEventMessage {

    Nanoseconds nanoseconds;
    EventCode event_code;
    Version version;
    Subversion subversion;

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
