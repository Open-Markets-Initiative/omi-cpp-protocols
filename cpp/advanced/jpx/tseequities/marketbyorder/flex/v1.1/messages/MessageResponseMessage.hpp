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

    flex_marketbyorder::tcp_packet_header header = {std::uint16_t(sizeof(flex_marketbyorder::tcp_packet_header) - 2), packet_type::enum_type::message_response_message};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(flex_marketbyorder::tcp_packet_header);

    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.packet_length.get().value();
        return (sz + 2) == sizeof(flex_marketbyorder::tcp_packet_header)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(flex_marketbyorder::tcp_packet_header));
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
