// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/details/HeartbeatBodyWriter.hpp
#pragma once

#include "../HeartbeatBody.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

class heartbeat_body_group_writer;
class heartbeat_body_admin_body_writer;

class heartbeat_body_admin_body_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    heartbeat_body_admin_body_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    heartbeat_body_admin_body_writer& add_entry(const xmt_quantumfeedlevel2::heartbeat_body_admin_body_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<xmt_quantumfeedlevel2::heartbeat_body*>(msg_start_)->header.num_body.set(count_);
        reinterpret_cast<xmt_quantumfeedlevel2::frame_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_ - 5));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class heartbeat_body_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    heartbeat_body_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    heartbeat_body_admin_body_writer start_admin_body() {
        return { msg_start_, pos_, end_ };
    }
};


inline heartbeat_body_group_writer start_group_write(heartbeat_body& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + heartbeat_body::tail_capacity };
}
}
