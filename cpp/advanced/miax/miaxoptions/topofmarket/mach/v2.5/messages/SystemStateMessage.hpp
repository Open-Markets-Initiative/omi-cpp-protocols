#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/ToMVersion.hpp"
#include "../types/SessionId.hpp"
#include "../types/SystemStatus.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// System State Message
struct system_state_message {

    struct fields_type {
        mach_topofmarket::nanoseconds nanoseconds;
        mach_topofmarket::to_m_version to_m_version;
        mach_topofmarket::session_id session_id;
        mach_topofmarket::system_status system_status;
    };

    mach_topofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_topofmarket::packet_length packet_length;
    mach_topofmarket::packet_type packet_type = mach_topofmarket::packet_type::enum_type::application_message;
    mach_topofmarket::session_number session_number;
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
static_assert(offsetof(system_state_message::fields_type, nanoseconds) == 0, "unexpected offset of system_state_message::fields_type::nanoseconds");
static_assert(offsetof(system_state_message::fields_type, to_m_version) == 4, "unexpected offset of system_state_message::fields_type::to_m_version");
static_assert(offsetof(system_state_message::fields_type, session_id) == 12, "unexpected offset of system_state_message::fields_type::session_id");
static_assert(offsetof(system_state_message::fields_type, system_status) == 16, "unexpected offset of system_state_message::fields_type::system_status");
static_assert(sizeof(system_state_message::fields_type) == 17, "unexpected sizeof system_state_message::fields_type");
static_assert(sizeof(system_state_message) == sizeof(mach_topofmarket::sequence_number) + sizeof(mach_topofmarket::packet_length) + sizeof(mach_topofmarket::packet_type) + sizeof(mach_topofmarket::session_number) + sizeof(mach_topofmarket::message_type) + 17, "unexpected sizeof system_state_message");

#pragma pack(pop)
}
