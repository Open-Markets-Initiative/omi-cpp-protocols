#pragma once

#include <cstddef>
#include "../structs/TcpPacketHeader.hpp"
#include "../types/MulticastGroupNumber.hpp"
#include "../types/ResultCode.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Login Result Message
struct login_result_message {

    struct fields_type {
        flex_marketbyorder::multicast_group_number multicast_group_number;
        flex_marketbyorder::result_code result_code;
    };

    tcp_packet_header header = {std::uint16_t(sizeof(tcp_packet_header) + sizeof(fields_type)), packet_type::enum_type::login_result_message};

    fields_type fields;

    // parse method
    static login_result_message* parse(std::byte* buffer) {
        return reinterpret_cast<login_result_message*>(buffer);
    }

    // parse method const
    static const login_result_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const login_result_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(login_result_message::fields_type, multicast_group_number) == 0, "unexpected offset of login_result_message::fields_type::multicast_group_number");
static_assert(offsetof(login_result_message::fields_type, result_code) == 1, "unexpected offset of login_result_message::fields_type::result_code");
static_assert(sizeof(login_result_message::fields_type) == 2, "unexpected sizeof login_result_message::fields_type");
static_assert(sizeof(login_result_message) == sizeof(tcp_packet_header) + 2, "unexpected sizeof login_result_message");

#pragma pack(pop)
}
