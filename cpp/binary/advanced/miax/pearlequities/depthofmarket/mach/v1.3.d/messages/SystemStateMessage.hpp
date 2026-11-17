// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/SystemStateMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/DoMVersion.hpp"
#include "../types/SessionId.hpp"
#include "../types/SystemStatus.hpp"
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

    mach_depthofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_depthofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_depthofmarket::message_type)), mach_packet_type::enum_type::application_message, {}};
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
static_assert(sizeof(system_state_message) == sizeof(mach_depthofmarket::mach_packet_header) + sizeof(mach_depthofmarket::message_type) + 14, "unexpected sizeof system_state_message");

#pragma pack(pop)
}
