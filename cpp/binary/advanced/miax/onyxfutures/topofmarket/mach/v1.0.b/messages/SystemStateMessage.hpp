// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/SystemStateMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TomVersion.hpp"
#include "../types/SessionId.hpp"
#include "../types/SystemStatus.hpp"
#include "../types/MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

#pragma pack(push, 1)

// System State Message
struct system_state_message {

    struct fields_type {
        mach_topofmarket::timestamp timestamp;
        mach_topofmarket::tom_version tom_version;
        mach_topofmarket::session_id session_id;
        mach_topofmarket::system_status system_status;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::system_state_message;

    fields_type fields;

    // parse method
    static system_state_message* parse(std::byte* buffer) {
        return reinterpret_cast<system_state_message*>(buffer);
    }

    // parse method const
    static const system_state_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const system_state_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(system_state_message::fields_type, timestamp) == 0, "unexpected offset of system_state_message::fields_type::timestamp");
static_assert(offsetof(system_state_message::fields_type, tom_version) == 8, "unexpected offset of system_state_message::fields_type::tom_version");
static_assert(offsetof(system_state_message::fields_type, session_id) == 16, "unexpected offset of system_state_message::fields_type::session_id");
static_assert(offsetof(system_state_message::fields_type, system_status) == 17, "unexpected offset of system_state_message::fields_type::system_status");
static_assert(sizeof(system_state_message::fields_type) == 18, "unexpected sizeof system_state_message::fields_type");
static_assert(sizeof(system_state_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 18, "unexpected sizeof system_state_message");

#pragma pack(pop)
}
