// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/details/GoodbyePacketWriter.hpp
#pragma once

#include "../GoodbyePacket.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

class goodbye_packet_group_writer;

class goodbye_packet_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    goodbye_packet_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> logout_text_and_finish(std::string_view v) {
        if (pos_ + v.size() > end_) throw std::runtime_error("buffer overrun writing external-length var-data");
        std::memcpy(pos_, v.data(), v.size());
        auto* next_pos = pos_ + v.size();
        reinterpret_cast<mach_depthofmarket::esesm_packet_header*>(msg_start_)->esesm_packet_length.set(static_cast<uint16_t>(next_pos - msg_start_ - 2));
        return { msg_start_, static_cast<size_t>(next_pos - msg_start_) };
    }
};


inline goodbye_packet_group_writer start_group_write(goodbye_packet& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + goodbye_packet::tail_capacity };
}
}
