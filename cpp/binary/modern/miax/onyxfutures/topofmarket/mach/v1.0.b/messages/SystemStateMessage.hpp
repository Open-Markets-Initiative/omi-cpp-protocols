#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TomVersion.hpp"
#include "../types/SessionId.hpp"
#include "../types/SystemStatus.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

#pragma pack(push, 1)

// 
struct SystemStateMessage {

    Timestamp timestamp;
    TomVersion tom_version;
    SessionId session_id;
    SystemStatus system_status;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 3;

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
