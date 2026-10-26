#pragma once

#include "../SequencedDataPacket.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

class sequenced_data_packet_group_writer;

class sequenced_data_packet_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    sequenced_data_packet_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> sequenced_message_and_finish(std::string_view v) {
        if (pos_ + v.size() > end_) throw std::runtime_error("buffer overrun writing external-length var-data");
        std::memcpy(pos_, v.data(), v.size());
        auto* next_pos = pos_ + v.size();
        reinterpret_cast<itch_totalview::server_packet_header*>(msg_start_)->packet_length.set(static_cast<uint16_t>(next_pos - msg_start_ - 2));
        return { msg_start_, static_cast<size_t>(next_pos - msg_start_) };
    }
};


inline sequenced_data_packet_group_writer start_group_write(sequenced_data_packet& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + sequenced_data_packet::tail_capacity };
}
}
