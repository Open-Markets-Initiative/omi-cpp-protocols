#pragma once

#include "../FractionalApproximateAdjustedVolumeMarketCenterMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

class fractional_approximate_adjusted_volume_market_center_message_group_writer;
class fractional_approximate_adjusted_volume_market_center_message_participant_writer;

class fractional_approximate_adjusted_volume_market_center_message_participant_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    fractional_approximate_adjusted_volume_market_center_message_participant_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    fractional_approximate_adjusted_volume_market_center_message_participant_writer& add_entry(const cta_output::fractional_approximate_adjusted_volume_market_center_message_participant_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<cta_output::fractional_approximate_adjusted_volume_market_center_message*>(msg_start_)->fields.number_of_participants.set(count_);
        reinterpret_cast<cta_output::fractional_approximate_adjusted_volume_market_center_message*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_ - sizeof(cta_output::block_header)));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class fractional_approximate_adjusted_volume_market_center_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    fractional_approximate_adjusted_volume_market_center_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    fractional_approximate_adjusted_volume_market_center_message_participant_writer start_participant() {
        return { msg_start_, pos_, end_ };
    }
};


inline fractional_approximate_adjusted_volume_market_center_message_group_writer start_group_write(fractional_approximate_adjusted_volume_market_center_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + fractional_approximate_adjusted_volume_market_center_message::tail_capacity };
}
}
