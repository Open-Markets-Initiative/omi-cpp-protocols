// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: structs/MachPacketHeader.hpp
#pragma once

#include <cstddef>
#include "../types/SequenceNumber.hpp"
#include "../types/MachPacketLength.hpp"
#include "../types/MachPacketType.hpp"
#include "../types/SessionNumber.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

struct mach_packet_header {

    mach_depthofmarket::sequence_number sequence_number;
    mach_depthofmarket::mach_packet_length mach_packet_length;
    mach_depthofmarket::mach_packet_type mach_packet_type;
    mach_depthofmarket::session_number session_number;

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
static_assert(offsetof(mach_packet_header, mach_packet_length) == 8, "unexpected offset of mach_packet_header::mach_packet_length");
static_assert(offsetof(mach_packet_header, mach_packet_type) == 10, "unexpected offset of mach_packet_header::mach_packet_type");
static_assert(offsetof(mach_packet_header, session_number) == 11, "unexpected offset of mach_packet_header::session_number");
static_assert(sizeof(mach_packet_header) == 12, "unexpected sizeof mach_packet_header");

#pragma pack(pop)
}
