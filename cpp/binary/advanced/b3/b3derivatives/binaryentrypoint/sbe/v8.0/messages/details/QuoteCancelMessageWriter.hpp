#pragma once

#include "../QuoteCancelMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

class quote_cancel_message_group_writer;
class quote_cancel_message_after_quote_req_id;
class quote_cancel_message_after_desk_id;

class quote_cancel_message_after_quote_req_id {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    quote_cancel_message_after_quote_req_id(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    quote_cancel_message_after_desk_id desk_id(std::string_view v);
};

class quote_cancel_message_after_desk_id {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    quote_cancel_message_after_desk_id(std::byte* msg_start, std::byte* pos, std::byte* end)
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

class quote_cancel_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    quote_cancel_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    quote_cancel_message_after_quote_req_id quote_req_id(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
        return { msg_start_, next_pos, end_ };
    }
};

inline quote_cancel_message_after_desk_id quote_cancel_message_after_quote_req_id::desk_id(std::string_view v) {
    if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
    std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
    return { msg_start_, next_pos, end_ };
}



inline quote_cancel_message_group_writer start_group_write(quote_cancel_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + quote_cancel_message::tail_capacity };
}
}
