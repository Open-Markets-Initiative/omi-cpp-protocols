// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/SystemTimeMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Seconds.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// System Time Message
struct system_time_message {

    struct fields_type {
        mach_depthofmarket::seconds seconds;
    };

    mach_depthofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_depthofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_depthofmarket::message_type)), mach_packet_type::enum_type::application_message, {}};
    mach_depthofmarket::message_type message_type = mach_depthofmarket::message_type::enum_type::system_time_message;

    fields_type fields;

    // parse method
    static system_time_message* parse(std::byte* buffer) {
        return reinterpret_cast<system_time_message*>(buffer);
    }

    // parse method const
    static const system_time_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const system_time_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(system_time_message::fields_type, seconds) == 0, "unexpected offset of system_time_message::fields_type::seconds");
static_assert(sizeof(system_time_message::fields_type) == 4, "unexpected sizeof system_time_message::fields_type");
static_assert(sizeof(system_time_message) == sizeof(mach_depthofmarket::mach_packet_header) + sizeof(mach_depthofmarket::message_type) + 4, "unexpected sizeof system_time_message");

#pragma pack(pop)
}
