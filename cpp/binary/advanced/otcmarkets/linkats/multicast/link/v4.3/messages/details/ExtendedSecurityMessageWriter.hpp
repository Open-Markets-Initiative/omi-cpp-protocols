// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/details/ExtendedSecurityMessageWriter.hpp
#pragma once

#include "../ExtendedSecurityMessage.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

namespace link_multicast = ::otcmarkets::linkats::multicast::link::v4_3;

class extended_security_message_group_writer;
class extended_security_message_after_security_detail;

class extended_security_message_after_security_detail {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    extended_security_message_after_security_detail(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> issuer_and_finish(std::string_view v) {
        if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
        std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
        auto* final_pos = pos_ + sizeof(std::uint8_t) + v.size();
        reinterpret_cast<link_multicast::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(final_pos - msg_start_));
        return { msg_start_, static_cast<size_t>(final_pos - msg_start_) };
    }
};

class extended_security_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    extended_security_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    extended_security_message_after_security_detail security_detail(std::string_view v) {
        if (pos_ + sizeof(std::uint8_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<std::uint8_t*>(pos_) = static_cast<std::uint8_t>(v.size());
        std::memcpy(pos_ + sizeof(std::uint8_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(std::uint8_t) + v.size();
        return { msg_start_, next_pos, end_ };
    }
};


inline extended_security_message_group_writer start_group_write(extended_security_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + extended_security_message::tail_capacity };
}
}
