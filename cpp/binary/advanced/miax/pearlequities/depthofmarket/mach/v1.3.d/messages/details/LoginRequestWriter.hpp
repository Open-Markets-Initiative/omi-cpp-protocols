// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: messages/details/LoginRequestWriter.hpp
#pragma once

#include "../LoginRequest.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

class login_request_group_writer;
class login_request_requested_matching_engine_writer;

class login_request_requested_matching_engine_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    login_request_requested_matching_engine_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    login_request_requested_matching_engine_writer& add_entry(const mach_depthofmarket::login_request_requested_matching_engine_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<mach_depthofmarket::login_request*>(msg_start_)->fields.number_of_matching_engines.set(count_);
        reinterpret_cast<mach_depthofmarket::esesm_packet_header*>(msg_start_)->esesm_packet_length.set(static_cast<uint16_t>(pos_ - msg_start_ - 2));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class login_request_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    login_request_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    login_request_requested_matching_engine_writer start_requested_matching_engine() {
        return { msg_start_, pos_, end_ };
    }
};


inline login_request_group_writer start_group_write(login_request& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + login_request::tail_capacity };
}
}
