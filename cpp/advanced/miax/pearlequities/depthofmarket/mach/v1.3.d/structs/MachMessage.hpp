#pragma once

#include <cstddef>
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

struct mach_message {

    mach_depthofmarket::sequence_number sequence_number;
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type;
    mach_depthofmarket::session_number session_number;

    // parse method
    static mach_message* parse(std::byte* buffer) {
        return reinterpret_cast<mach_message*>(buffer);
    }

    // parse method const
    static const mach_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const mach_message*>(buffer);
    }
};

#pragma pack(pop)
}
