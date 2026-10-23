#pragma once

#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct MachMessage {

    SequenceNumber sequence_number;
    MachPacketLength mach_packet_length;
    MachPacketType mach_packet_type;
    SessionNumber session_number;

    // parse method
    static MachMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MachMessage*>(buffer);
    }

    // parse method const
    static const MachMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MachMessage*>(buffer);
    }
};

#pragma pack(pop)
}
