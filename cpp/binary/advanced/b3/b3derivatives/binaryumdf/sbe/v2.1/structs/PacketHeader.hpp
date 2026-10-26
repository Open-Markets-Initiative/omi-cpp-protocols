#pragma once

#include <cstddef>
#include "../types/ChannelId.hpp"
#include "../types/PacketReserved.hpp"
#include "../types/SequenceVersion.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/SendingTime.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_1;

#pragma pack(push, 1)

struct packet_header {

    sbe_binaryumdf::channel_id channel_id;
    sbe_binaryumdf::packet_reserved packet_reserved;
    sbe_binaryumdf::sequence_version sequence_version;
    sbe_binaryumdf::sequence_number sequence_number;
    sbe_binaryumdf::sending_time sending_time;

    // parse method
    static packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<packet_header*>(buffer);
    }

    // parse method const
    static const packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(packet_header, channel_id) == 0, "unexpected offset of packet_header::channel_id");
static_assert(offsetof(packet_header, packet_reserved) == 1, "unexpected offset of packet_header::packet_reserved");
static_assert(offsetof(packet_header, sequence_version) == 2, "unexpected offset of packet_header::sequence_version");
static_assert(offsetof(packet_header, sequence_number) == 4, "unexpected offset of packet_header::sequence_number");
static_assert(offsetof(packet_header, sending_time) == 8, "unexpected offset of packet_header::sending_time");
static_assert(sizeof(packet_header) == 16, "unexpected sizeof packet_header");

#pragma pack(pop)
}
