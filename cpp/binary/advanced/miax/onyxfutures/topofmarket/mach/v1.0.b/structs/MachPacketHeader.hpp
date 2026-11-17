// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: structs/MachPacketHeader.hpp
#pragma once

#include <cstddef>
#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

#pragma pack(push, 1)

struct mach_packet_header {

    mach_topofmarket::sequence_number sequence_number;
    mach_topofmarket::packet_length packet_length;
    mach_topofmarket::packet_type packet_type;
    mach_topofmarket::session_number session_number;

    // parse method
    static mach_packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<mach_packet_header*>(buffer);
    }

    // parse method const
    static const mach_packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const mach_packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(mach_packet_header, sequence_number) == 0, "unexpected offset of mach_packet_header::sequence_number");
static_assert(offsetof(mach_packet_header, packet_length) == 8, "unexpected offset of mach_packet_header::packet_length");
static_assert(offsetof(mach_packet_header, packet_type) == 10, "unexpected offset of mach_packet_header::packet_type");
static_assert(offsetof(mach_packet_header, session_number) == 11, "unexpected offset of mach_packet_header::session_number");
static_assert(sizeof(mach_packet_header) == 12, "unexpected sizeof mach_packet_header");

#pragma pack(pop)
}
