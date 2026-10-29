#pragma once

#include "../OrderCancelReplaceRequestMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

class order_cancel_replace_request_message_group_writer;
class order_cancel_replace_request_message_after_desk_id;

class order_cancel_replace_request_message_after_desk_id {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    order_cancel_replace_request_message_after_desk_id(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> memo_and_finish(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* final_pos = pos_ + sizeof(uint32_t) + v.size();
        reinterpret_cast<sbe_binaryentrypoint::simple_open_framing_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(final_pos - msg_start_));
        return { msg_start_, static_cast<size_t>(final_pos - msg_start_) };
    }
};

class order_cancel_replace_request_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    order_cancel_replace_request_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    order_cancel_replace_request_message_after_desk_id desk_id(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
        return { msg_start_, next_pos, end_ };
    }
};


inline order_cancel_replace_request_message_group_writer start_group_write(order_cancel_replace_request_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + order_cancel_replace_request_message::tail_capacity };
}
}
