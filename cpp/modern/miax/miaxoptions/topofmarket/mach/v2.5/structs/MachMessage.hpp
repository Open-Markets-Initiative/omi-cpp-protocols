#pragma once

#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

struct MachMessage {

    SequenceNumber sequence_number;
    PacketLength packet_length;
    PacketType packet_type;
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
