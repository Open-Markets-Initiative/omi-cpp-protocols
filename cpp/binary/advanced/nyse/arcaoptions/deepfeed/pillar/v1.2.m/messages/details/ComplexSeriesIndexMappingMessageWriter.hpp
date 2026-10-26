#pragma once

#include "../ComplexSeriesIndexMappingMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

class complex_series_index_mapping_message_group_writer;
class complex_series_index_mapping_message_complex_series_index_mapping_leg_writer;

class complex_series_index_mapping_message_complex_series_index_mapping_leg_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint16_t count_ = 0;

public:
    complex_series_index_mapping_message_complex_series_index_mapping_leg_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_series_index_mapping_message_complex_series_index_mapping_leg_writer& add_entry(const pillar_deepfeed::complex_series_index_mapping_message_complex_series_index_mapping_leg_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<pillar_deepfeed::complex_series_index_mapping_message*>(msg_start_)->fields.no_of_legs.set(count_);
        reinterpret_cast<pillar_deepfeed::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class complex_series_index_mapping_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    complex_series_index_mapping_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_series_index_mapping_message_complex_series_index_mapping_leg_writer start_complex_series_index_mapping_leg() {
        return { msg_start_, pos_, end_ };
    }
};


inline complex_series_index_mapping_message_group_writer start_group_write(complex_series_index_mapping_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + complex_series_index_mapping_message::tail_capacity };
}
}
