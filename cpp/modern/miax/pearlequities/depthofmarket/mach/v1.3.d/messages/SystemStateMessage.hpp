#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/DoMVersion.hpp"
#include "../types/SessionId.hpp"
#include "../types/SystemStatus.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This is the message format that will be used to notify firms of the state changes of the system. This is a notification that applies to all symbols on the feed.
struct SystemStateMessage {

    Nanoseconds nanoseconds;
    DoMVersion do_m_version;
    SessionId session_id;
    SystemStatus system_status;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 83;

    // parse method
    static SystemStateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SystemStateMessage*>(buffer);
    }

    // parse method const
    static const SystemStateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SystemStateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SystemStateMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SystemStateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
