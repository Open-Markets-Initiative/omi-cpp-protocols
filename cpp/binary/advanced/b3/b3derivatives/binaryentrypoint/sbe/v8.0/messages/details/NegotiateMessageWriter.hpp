#pragma once

#include "../NegotiateMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

class negotiate_message_group_writer;
class negotiate_message_after_credentials;
class negotiate_message_after_client_ip;
class negotiate_message_after_client_app_name;

class negotiate_message_after_credentials {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    negotiate_message_after_credentials(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    negotiate_message_after_client_ip client_ip(std::string_view v);
};

class negotiate_message_after_client_ip {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    negotiate_message_after_client_ip(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    negotiate_message_after_client_app_name client_app_name(std::string_view v);
};

class negotiate_message_after_client_app_name {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    negotiate_message_after_client_app_name(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> client_app_version_and_finish(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* final_pos = pos_ + sizeof(uint32_t) + v.size();
        reinterpret_cast<sbe_binaryentrypoint::simple_open_framing_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(final_pos - msg_start_));
        return { msg_start_, static_cast<size_t>(final_pos - msg_start_) };
    }
};

class negotiate_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    negotiate_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    negotiate_message_after_credentials credentials(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
        return { msg_start_, next_pos, end_ };
    }
};

inline negotiate_message_after_client_ip negotiate_message_after_credentials::client_ip(std::string_view v) {
    if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
    std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
    return { msg_start_, next_pos, end_ };
}

inline negotiate_message_after_client_app_name negotiate_message_after_client_ip::client_app_name(std::string_view v) {
    if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
    std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
    return { msg_start_, next_pos, end_ };
}



inline negotiate_message_group_writer start_group_write(negotiate_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + negotiate_message::tail_capacity };
}
}
