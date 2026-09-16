#pragma once

#include "../MessageResponseMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

class message_response_message_group_writer;

class message_response_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    message_response_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> data_and_finish(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
        reinterpret_cast<flex_marketbyorder::tcp_packet_header*>(msg_start_)->packet_length.set(static_cast<uint16_t>(next_pos - msg_start_));
        return { msg_start_, static_cast<size_t>(next_pos - msg_start_) };
    }
};


inline message_response_message_group_writer start_group_write(message_response_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + message_response_message::tail_capacity };
}
}
