#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// System Time Message
struct system_time_message {

    struct fields_type {
        mach_depthofmarket::seconds seconds;
    };

    mach_depthofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type = mach_depthofmarket::mach_packet_type::enum_type::application_message;
    mach_depthofmarket::session_number session_number;
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
static_assert(sizeof(system_time_message) == sizeof(mach_depthofmarket::sequence_number) + sizeof(mach_depthofmarket::mach_packet_length) + sizeof(mach_depthofmarket::mach_packet_type) + sizeof(mach_depthofmarket::session_number) + sizeof(mach_depthofmarket::message_type) + 4, "unexpected sizeof system_time_message");

#pragma pack(pop)
}
