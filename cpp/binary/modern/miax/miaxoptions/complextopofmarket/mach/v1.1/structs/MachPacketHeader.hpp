#pragma once

#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

struct MachPacketHeader {

    SequenceNumber sequence_number;
    PacketLength packet_length;
    PacketType packet_type;
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
