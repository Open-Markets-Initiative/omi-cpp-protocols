// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/SystemStateMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/CToMVersion.hpp"
#include "../types/SessionId.hpp"
#include "../types/SystemStatus.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

#pragma pack(push, 1)

// System State Message
struct system_state_message {

    struct fields_type {
        mach_complextopofmarket::nanoseconds nanoseconds;
        mach_complextopofmarket::c_to_m_version c_to_m_version;
        mach_complextopofmarket::session_id session_id;
        mach_complextopofmarket::system_status system_status;
    };

    mach_complextopofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_complextopofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_complextopofmarket::message_type message_type = mach_complextopofmarket::message_type::enum_type::system_state_message;

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
static_assert(offsetof(system_state_message::fields_type, c_to_m_version) == 4, "unexpected offset of system_state_message::fields_type::c_to_m_version");
static_assert(offsetof(system_state_message::fields_type, session_id) == 12, "unexpected offset of system_state_message::fields_type::session_id");
static_assert(offsetof(system_state_message::fields_type, system_status) == 16, "unexpected offset of system_state_message::fields_type::system_status");
static_assert(sizeof(system_state_message::fields_type) == 17, "unexpected sizeof system_state_message::fields_type");
static_assert(sizeof(system_state_message) == sizeof(mach_complextopofmarket::mach_packet_header) + sizeof(mach_complextopofmarket::message_type) + 17, "unexpected sizeof system_state_message");

#pragma pack(pop)
}
