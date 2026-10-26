#pragma once

#include "../MdpsessionmgmtMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

class mdpsessionmgmt_message_group_writer;

class mdpsessionmgmt_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    mdpsessionmgmt_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> mdpsessionmgmt_payload_and_finish(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
        reinterpret_cast<sbe_mdp3::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(next_pos - msg_start_));
        return { msg_start_, static_cast<size_t>(next_pos - msg_start_) };
    }
};


inline mdpsessionmgmt_message_group_writer start_group_write(mdpsessionmgmt_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + mdpsessionmgmt_message::tail_capacity };
}
}
