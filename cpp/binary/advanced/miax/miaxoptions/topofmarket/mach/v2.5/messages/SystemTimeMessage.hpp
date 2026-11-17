// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: messages/SystemTimeMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Seconds.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// System Time Message
struct system_time_message {

    struct fields_type {
        mach_topofmarket::seconds seconds;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::system_time_message;

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
static_assert(sizeof(system_time_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 4, "unexpected sizeof system_time_message");

#pragma pack(pop)
}
