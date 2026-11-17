// OtcMarkets.LinkAts.Multicast.Link.v4.3: structs/PacketHeader.hpp
#pragma once

#include <cstddef>
#include "../types/PacketSize.hpp"
#include "../types/SeqNum.hpp"
#include "../types/PacketFlag.hpp"
#include "../types/MessageCount.hpp"
#include "../types/PacketMilli.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

#pragma pack(push, 1)

struct packet_header {

    link_multicast::packet_size packet_size;
    link_multicast::seq_num seq_num;
    link_multicast::packet_flag packet_flag;
    link_multicast::message_count message_count;
    link_multicast::packet_milli packet_milli;

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
static_assert(offsetof(packet_header, seq_num) == 2, "unexpected offset of packet_header::seq_num");
static_assert(offsetof(packet_header, packet_flag) == 6, "unexpected offset of packet_header::packet_flag");
static_assert(offsetof(packet_header, message_count) == 7, "unexpected offset of packet_header::message_count");
static_assert(offsetof(packet_header, packet_milli) == 8, "unexpected offset of packet_header::packet_milli");
static_assert(sizeof(packet_header) == 12, "unexpected sizeof packet_header");

#pragma pack(pop)
}
