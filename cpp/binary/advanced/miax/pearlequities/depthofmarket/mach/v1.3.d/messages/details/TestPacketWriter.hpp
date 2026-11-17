// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/details/TestPacketWriter.hpp
#pragma once

#include "../TestPacket.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

class test_packet_group_writer;

class test_packet_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    test_packet_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> test_text_and_finish(std::string_view v) {
        if (pos_ + v.size() > end_) throw std::runtime_error("buffer overrun writing external-length var-data");
        std::memcpy(pos_, v.data(), v.size());
        auto* next_pos = pos_ + v.size();
        reinterpret_cast<mach_depthofmarket::esesm_packet_header*>(msg_start_)->esesm_packet_length.set(static_cast<uint16_t>(next_pos - msg_start_ - 2));
        return { msg_start_, static_cast<size_t>(next_pos - msg_start_) };
    }
};


inline test_packet_group_writer start_group_write(test_packet& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + test_packet::tail_capacity };
}
}
