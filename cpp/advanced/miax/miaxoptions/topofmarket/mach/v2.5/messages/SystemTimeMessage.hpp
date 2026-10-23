#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// System Time Message
struct system_time_message {

    struct fields_type {
        mach_topofmarket::seconds seconds;
    };

    mach_topofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_topofmarket::packet_length packet_length;
    mach_topofmarket::packet_type packet_type = mach_topofmarket::packet_type::enum_type::application_message;
    mach_topofmarket::session_number session_number;
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
static_assert(sizeof(system_time_message) == sizeof(mach_topofmarket::sequence_number) + sizeof(mach_topofmarket::packet_length) + sizeof(mach_topofmarket::packet_type) + sizeof(mach_topofmarket::session_number) + sizeof(mach_topofmarket::message_type) + 4, "unexpected sizeof system_time_message");

#pragma pack(pop)
}
