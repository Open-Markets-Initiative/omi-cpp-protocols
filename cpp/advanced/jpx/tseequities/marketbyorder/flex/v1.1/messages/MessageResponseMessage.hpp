#pragma once

#include <cstddef>
#include "../structs/TcpPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;


#pragma pack(push, 1)

// Message Response Message
struct message_response_message {

    struct fields_type {
    };

    tcp_packet_header header = {std::uint16_t(sizeof(tcp_packet_header) + sizeof(fields_type)), packet_type::enum_type::message_response_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(tcp_packet_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.packet_length.get().value();
        return sz == sizeof(tcp_packet_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(tcp_packet_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    sbe_var_data data() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static message_response_message* parse(std::byte* buffer) {
        return reinterpret_cast<message_response_message*>(buffer);
    }

    // parse method const
    static const message_response_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const message_response_message*>(buffer);
    }

};

// layout verification
static_assert(sizeof(message_response_message::fields_type) == 1, "unexpected sizeof message_response_message::fields_type");

#pragma pack(pop)
}

#include "details/MessageResponseMessageWriter.hpp"
#include "details/MessageResponseMessageReader.hpp"
