#pragma once

#include <cstddef>
#include "../types/SesmPacketLength.hpp"
#include "../types/SesmPacketType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

struct sesm_packet_header {

    mach_topofmarket::sesm_packet_length sesm_packet_length;
    mach_topofmarket::sesm_packet_type sesm_packet_type;

    // parse method
    static sesm_packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<sesm_packet_header*>(buffer);
    }

    // parse method const
    static const sesm_packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const sesm_packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(sesm_packet_header, sesm_packet_length) == 0, "unexpected offset of sesm_packet_header::sesm_packet_length");
static_assert(offsetof(sesm_packet_header, sesm_packet_type) == 2, "unexpected offset of sesm_packet_header::sesm_packet_type");
static_assert(sizeof(sesm_packet_header) == 3, "unexpected sizeof sesm_packet_header");

#pragma pack(pop)
}
