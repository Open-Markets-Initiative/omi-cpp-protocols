#pragma once

#include "../SnapshotDataMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;

class snapshot_data_message_group_writer;

class snapshot_data_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    snapshot_data_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> iex_tp_message_data_and_finish(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
        reinterpret_cast<snap_tops::message_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(next_pos - msg_start_ - 2));
        return { msg_start_, static_cast<size_t>(next_pos - msg_start_) };
    }
};


inline snapshot_data_message_group_writer start_group_write(snapshot_data_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + snapshot_data_message::tail_capacity };
}
}
