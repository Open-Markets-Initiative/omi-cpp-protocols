#pragma once

#include <cstddef>
#include "../types/PacketSize.hpp"
#include "../types/DeliveryFlag.hpp"
#include "../types/MessageCount.hpp"
#include "../types/SequenceNumber.hpp"
#include "../structs/SendTime.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

namespace xdp_bbo = ::nyse::nyseequities::bbo::xdp::v2_4_g;

#pragma pack(push, 1)

struct packet_header {

    xdp_bbo::packet_size packet_size;
    xdp_bbo::delivery_flag delivery_flag;
    xdp_bbo::message_count message_count;
    xdp_bbo::sequence_number sequence_number;
    xdp_bbo::send_time send_time;

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
static_assert(offsetof(packet_header, packet_size) == 0, "unexpected offset of packet_header::packet_size");
static_assert(offsetof(packet_header, delivery_flag) == 2, "unexpected offset of packet_header::delivery_flag");
static_assert(offsetof(packet_header, message_count) == 3, "unexpected offset of packet_header::message_count");
static_assert(offsetof(packet_header, sequence_number) == 4, "unexpected offset of packet_header::sequence_number");
static_assert(offsetof(packet_header, send_time) == 8, "unexpected offset of packet_header::send_time");
static_assert(sizeof(packet_header) == 16, "unexpected sizeof packet_header");

#pragma pack(pop)
}
