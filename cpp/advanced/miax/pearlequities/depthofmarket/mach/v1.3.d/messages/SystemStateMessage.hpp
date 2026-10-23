#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/DoMVersion.hpp"
#include "../types/SessionId.hpp"
#include "../types/SystemStatus.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// System State Message
struct system_state_message {

    struct fields_type {
        mach_depthofmarket::nanoseconds nanoseconds;
        mach_depthofmarket::do_m_version do_m_version;
        mach_depthofmarket::session_id session_id;
        mach_depthofmarket::system_status system_status;
    };

    mach_depthofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type = mach_depthofmarket::mach_packet_type::enum_type::application_message;
    mach_depthofmarket::session_number session_number;
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::system_state_message;

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
static_assert(offsetof(system_state_message::fields_type, do_m_version) == 4, "unexpected offset of system_state_message::fields_type::do_m_version");
static_assert(offsetof(system_state_message::fields_type, session_id) == 12, "unexpected offset of system_state_message::fields_type::session_id");
static_assert(offsetof(system_state_message::fields_type, system_status) == 13, "unexpected offset of system_state_message::fields_type::system_status");
static_assert(sizeof(system_state_message::fields_type) == 14, "unexpected sizeof system_state_message::fields_type");
static_assert(sizeof(system_state_message) == sizeof(mach_depthofmarket::sequence_number) + sizeof(mach_depthofmarket::mach_packet_length) + sizeof(mach_depthofmarket::mach_packet_type) + sizeof(mach_depthofmarket::session_number) + sizeof(mach_depthofmarket::message_type) + 14, "unexpected sizeof system_state_message");

#pragma pack(pop)
}
