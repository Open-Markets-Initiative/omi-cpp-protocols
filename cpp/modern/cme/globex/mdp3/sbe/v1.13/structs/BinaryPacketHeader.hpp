#pragma once

#include "../types/PacketSequenceNumber.hpp"
#include "../types/SendingTime.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct BinaryPacketHeader {

    PacketSequenceNumber packet_sequence_number;
    SendingTime sending_time;

    // parse method
    static BinaryPacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<BinaryPacketHeader*>(buffer);
    }

    // parse method const
    static const BinaryPacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const BinaryPacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
