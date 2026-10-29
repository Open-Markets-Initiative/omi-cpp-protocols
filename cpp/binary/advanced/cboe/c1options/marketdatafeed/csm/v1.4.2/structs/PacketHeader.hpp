#pragma once

#include <cstddef>
#include "../types/Version.hpp"
#include "../types/PacketLength.hpp"
#include "../types/SendingTime.hpp"
#include "../types/MessageCount.hpp"
#include "../types/FirstMsgSeqNum.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct packet_header {

    csm_marketdatafeed::version version;
    csm_marketdatafeed::packet_length packet_length;
    csm_marketdatafeed::sending_time sending_time;
    csm_marketdatafeed::message_count message_count;
    csm_marketdatafeed::first_msg_seq_num first_msg_seq_num;

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
static_assert(offsetof(packet_header, version) == 0, "unexpected offset of packet_header::version");
static_assert(offsetof(packet_header, packet_length) == 1, "unexpected offset of packet_header::packet_length");
static_assert(offsetof(packet_header, sending_time) == 3, "unexpected offset of packet_header::sending_time");
static_assert(offsetof(packet_header, message_count) == 11, "unexpected offset of packet_header::message_count");
static_assert(offsetof(packet_header, first_msg_seq_num) == 12, "unexpected offset of packet_header::first_msg_seq_num");
static_assert(sizeof(packet_header) == 16, "unexpected sizeof packet_header");

#pragma pack(pop)
}
