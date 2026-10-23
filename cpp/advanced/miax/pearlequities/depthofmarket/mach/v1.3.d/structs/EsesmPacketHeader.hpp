#pragma once

#include <cstddef>
#include "../types/EsesmPacketLength.hpp"
#include "../types/EsesmPacketType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

struct esesm_packet_header {

    mach_depthofmarket::esesm_packet_length esesm_packet_length;
    mach_depthofmarket::esesm_packet_type esesm_packet_type;

    // parse method
    static esesm_packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<esesm_packet_header*>(buffer);
    }

    // parse method const
    static const esesm_packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const esesm_packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(esesm_packet_header, esesm_packet_length) == 0, "unexpected offset of esesm_packet_header::esesm_packet_length");
static_assert(offsetof(esesm_packet_header, esesm_packet_type) == 2, "unexpected offset of esesm_packet_header::esesm_packet_type");
static_assert(sizeof(esesm_packet_header) == 3, "unexpected sizeof esesm_packet_header");

#pragma pack(pop)
}
