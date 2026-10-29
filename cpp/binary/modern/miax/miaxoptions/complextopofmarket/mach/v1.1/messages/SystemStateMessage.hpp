#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/CToMVersion.hpp"
#include "../types/SessionId.hpp"
#include "../types/SystemStatus.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This message format is used to notify the firms of the state changes of the system. This is a notification that applies to each Underlying group. Firms can use notifications as triggers in their system to ensure electronic synchronization of systems.
struct SystemStateMessage {

    Nanoseconds nanoseconds;
    CToMVersion c_to_m_version;
    SessionId session_id;
    SystemStatus system_status;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'S';

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
