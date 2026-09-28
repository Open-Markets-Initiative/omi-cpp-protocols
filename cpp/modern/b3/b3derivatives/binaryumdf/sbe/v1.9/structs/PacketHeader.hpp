#pragma once

#include "../types/ChannelId.hpp"
#include "../types/PacketReserved.hpp"
#include "../types/SequenceVersion.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/SendingTime.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

#pragma pack(push, 1)

struct PacketHeader {

    ChannelId channel_id;
    PacketReserved packet_reserved;
    SequenceVersion sequence_version;
    SequenceNumber sequence_number;
    SendingTime sending_time;

    // parse method
    static PacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<PacketHeader*>(buffer);
    }

    // parse method const
    static const PacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const PacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
