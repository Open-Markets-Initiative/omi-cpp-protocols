#pragma once

#include <cstddef>
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

struct tcp_packet_header {

    flex_marketbyorder::packet_length packet_length;
    flex_marketbyorder::packet_type packet_type;

    // parse method
    static tcp_packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<tcp_packet_header*>(buffer);
    }

    // parse method const
    static const tcp_packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const tcp_packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(tcp_packet_header, packet_length) == 0, "unexpected offset of tcp_packet_header::packet_length");
static_assert(offsetof(tcp_packet_header, packet_type) == 2, "unexpected offset of tcp_packet_header::packet_type");
static_assert(sizeof(tcp_packet_header) == 3, "unexpected sizeof tcp_packet_header");

#pragma pack(pop)
}
