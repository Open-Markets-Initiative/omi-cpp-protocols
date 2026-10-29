#pragma once

#include <cstddef>
#include "../types/PktSize.hpp"
#include "../types/DeliveryFlag.hpp"
#include "../types/NumberMsgs.hpp"
#include "../types/SeqNum.hpp"
#include "../structs/SendTime.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

struct packet_header {

    pillar_topfeed::pkt_size pkt_size;
    pillar_topfeed::delivery_flag delivery_flag;
    pillar_topfeed::number_msgs number_msgs;
    pillar_topfeed::seq_num seq_num;
    pillar_topfeed::send_time send_time;

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
static_assert(offsetof(packet_header, pkt_size) == 0, "unexpected offset of packet_header::pkt_size");
static_assert(offsetof(packet_header, delivery_flag) == 2, "unexpected offset of packet_header::delivery_flag");
static_assert(offsetof(packet_header, number_msgs) == 3, "unexpected offset of packet_header::number_msgs");
static_assert(offsetof(packet_header, seq_num) == 4, "unexpected offset of packet_header::seq_num");
static_assert(offsetof(packet_header, send_time) == 8, "unexpected offset of packet_header::send_time");
static_assert(sizeof(packet_header) == 16, "unexpected sizeof packet_header");

#pragma pack(pop)
}
