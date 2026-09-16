#pragma once

#include <cstddef>
#include "../structs/TcpPacketHeader.hpp"
#include "../types/UserId.hpp"
#include "../types/MulticastGroupNumber.hpp"
#include "../types/NumberOfSystemReboots.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/RequestedMessageCount.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Login Request Message
struct login_request_message {

    struct fields_type {
        flex_marketbyorder::user_id user_id;
        flex_marketbyorder::multicast_group_number multicast_group_number;
        flex_marketbyorder::number_of_system_reboots number_of_system_reboots;
        flex_marketbyorder::sequence_number sequence_number;
        flex_marketbyorder::requested_message_count requested_message_count;
    };

    tcp_packet_header header = {std::uint16_t(sizeof(tcp_packet_header) + sizeof(fields_type)), packet_type::enum_type::login_request_message};

    fields_type fields;

    // parse method
    static login_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<login_request_message*>(buffer);
    }

    // parse method const
    static const login_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const login_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(login_request_message::fields_type, user_id) == 0, "unexpected offset of login_request_message::fields_type::user_id");
static_assert(offsetof(login_request_message::fields_type, multicast_group_number) == 6, "unexpected offset of login_request_message::fields_type::multicast_group_number");
static_assert(offsetof(login_request_message::fields_type, number_of_system_reboots) == 7, "unexpected offset of login_request_message::fields_type::number_of_system_reboots");
static_assert(offsetof(login_request_message::fields_type, sequence_number) == 8, "unexpected offset of login_request_message::fields_type::sequence_number");
static_assert(offsetof(login_request_message::fields_type, requested_message_count) == 12, "unexpected offset of login_request_message::fields_type::requested_message_count");
static_assert(sizeof(login_request_message::fields_type) == 15, "unexpected sizeof login_request_message::fields_type");
static_assert(sizeof(login_request_message) == sizeof(tcp_packet_header) + 15, "unexpected sizeof login_request_message");

#pragma pack(pop)
}
