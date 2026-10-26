#pragma once

#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct MachPacketHeader {

    SequenceNumber sequence_number;
    MachPacketLength mach_packet_length;
    MachPacketType mach_packet_type;
    SessionNumber session_number;

    // parse method
    static MachPacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<MachPacketHeader*>(buffer);
    }

    // parse method const
    static const MachPacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const MachPacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
