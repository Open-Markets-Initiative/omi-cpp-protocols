#pragma once

#include <cstddef>
#include "../types/MulticastGroupNumber.hpp"
#include "../types/NumberOfSystemReboots.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/IssueCode.hpp"
#include "../types/UpdateNumber.hpp"
#include "../types/PacketNumber.hpp"
#include "../types/TotalNumberOfPackets.hpp"
#include "../types/UtilityFlag.hpp"
#include "../types/MessageCount.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

struct packet_header {

    flex_marketbyorder::multicast_group_number multicast_group_number;
    flex_marketbyorder::number_of_system_reboots number_of_system_reboots;
    flex_marketbyorder::sequence_number sequence_number;
    flex_marketbyorder::issue_code issue_code;
    flex_marketbyorder::update_number update_number;
    flex_marketbyorder::packet_number packet_number;
    flex_marketbyorder::total_number_of_packets total_number_of_packets;
    flex_marketbyorder::utility_flag utility_flag;
    flex_marketbyorder::message_count message_count;

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
static_assert(offsetof(packet_header, multicast_group_number) == 0, "unexpected offset of packet_header::multicast_group_number");
static_assert(offsetof(packet_header, number_of_system_reboots) == 1, "unexpected offset of packet_header::number_of_system_reboots");
static_assert(offsetof(packet_header, sequence_number) == 2, "unexpected offset of packet_header::sequence_number");
static_assert(offsetof(packet_header, issue_code) == 6, "unexpected offset of packet_header::issue_code");
static_assert(offsetof(packet_header, update_number) == 18, "unexpected offset of packet_header::update_number");
static_assert(offsetof(packet_header, packet_number) == 22, "unexpected offset of packet_header::packet_number");
static_assert(offsetof(packet_header, total_number_of_packets) == 23, "unexpected offset of packet_header::total_number_of_packets");
static_assert(offsetof(packet_header, utility_flag) == 24, "unexpected offset of packet_header::utility_flag");
static_assert(offsetof(packet_header, message_count) == 25, "unexpected offset of packet_header::message_count");
static_assert(sizeof(packet_header) == 26, "unexpected sizeof packet_header");

#pragma pack(pop)
}
