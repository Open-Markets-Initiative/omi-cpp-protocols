#pragma once

#include "../RefreshResponseMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

class refresh_response_message_group_writer;

class refresh_response_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    refresh_response_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> application_message_and_finish(std::string_view v) {
        if (pos_ + v.size() > end_) throw std::runtime_error("buffer overrun writing external-length var-data");
        std::memcpy(pos_, v.data(), v.size());
        auto* next_pos = pos_ + v.size();
        reinterpret_cast<mach_topofmarket::sesm_packet_header*>(msg_start_)->sesm_packet_length.set(static_cast<uint16_t>(next_pos - msg_start_ - 2));
        return { msg_start_, static_cast<size_t>(next_pos - msg_start_) };
    }
};


inline refresh_response_message_group_writer start_group_write(refresh_response_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + refresh_response_message::tail_capacity };
}
}
