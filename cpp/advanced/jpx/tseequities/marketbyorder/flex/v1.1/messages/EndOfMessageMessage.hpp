#pragma once

#include <cstddef>
#include "../structs/TcpPacketHeader.hpp"
#include "../types/MulticastGroupNumber.hpp"
#include "../types/NumberOfSystemReboots.hpp"
#include "../types/NextSequenceNumber.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// End Of Message Message
struct end_of_message_message {

    struct fields_type {
        flex_marketbyorder::multicast_group_number multicast_group_number;
        flex_marketbyorder::number_of_system_reboots number_of_system_reboots;
        flex_marketbyorder::next_sequence_number next_sequence_number;
    };

    tcp_packet_header header = {std::uint16_t(sizeof(tcp_packet_header) + sizeof(fields_type)), packet_type::enum_type::end_of_message_message};

    fields_type fields;

    // parse method
    static end_of_message_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_message_message*>(buffer);
    }

    // parse method const
    static const end_of_message_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_message_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_message_message::fields_type, multicast_group_number) == 0, "unexpected offset of end_of_message_message::fields_type::multicast_group_number");
static_assert(offsetof(end_of_message_message::fields_type, number_of_system_reboots) == 1, "unexpected offset of end_of_message_message::fields_type::number_of_system_reboots");
static_assert(offsetof(end_of_message_message::fields_type, next_sequence_number) == 2, "unexpected offset of end_of_message_message::fields_type::next_sequence_number");
static_assert(sizeof(end_of_message_message::fields_type) == 6, "unexpected sizeof end_of_message_message::fields_type");
static_assert(sizeof(end_of_message_message) == sizeof(tcp_packet_header) + 6, "unexpected sizeof end_of_message_message");

#pragma pack(pop)
}
