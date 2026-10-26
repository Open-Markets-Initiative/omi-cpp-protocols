#pragma once

#include "../UnsequencedDataPacket.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2017;

class unsequenced_data_packet_group_writer;

class unsequenced_data_packet_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    unsequenced_data_packet_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> unsequenced_message_and_finish(std::string_view v) {
        if (pos_ + v.size() > end_) throw std::runtime_error("buffer overrun writing external-length var-data");
        std::memcpy(pos_, v.data(), v.size());
        auto* next_pos = pos_ + v.size();
        reinterpret_cast<itch_totalview::client_packet_header*>(msg_start_)->packet_length.set(static_cast<uint16_t>(next_pos - msg_start_ - 2));
        return { msg_start_, static_cast<size_t>(next_pos - msg_start_) };
    }
};


inline unsequenced_data_packet_group_writer start_group_write(unsequenced_data_packet& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + unsequenced_data_packet::tail_capacity };
}
}
