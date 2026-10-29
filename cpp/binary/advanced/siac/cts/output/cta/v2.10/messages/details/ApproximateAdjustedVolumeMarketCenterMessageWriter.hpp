#pragma once

#include "../ApproximateAdjustedVolumeMarketCenterMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

class approximate_adjusted_volume_market_center_message_group_writer;
class approximate_adjusted_volume_market_center_message_participants_writer;

class approximate_adjusted_volume_market_center_message_participants_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    approximate_adjusted_volume_market_center_message_participants_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    approximate_adjusted_volume_market_center_message_participants_writer& add_entry(const cta_output::approximate_adjusted_volume_market_center_message_participants_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<cta_output::approximate_adjusted_volume_market_center_message*>(msg_start_)->fields.number_of_participants.set(count_);
        reinterpret_cast<cta_output::approximate_adjusted_volume_market_center_message*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_ - sizeof(cta_output::block_header)));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class approximate_adjusted_volume_market_center_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    approximate_adjusted_volume_market_center_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    approximate_adjusted_volume_market_center_message_participants_writer start_participants() {
        return { msg_start_, pos_, end_ };
    }
};


inline approximate_adjusted_volume_market_center_message_group_writer start_group_write(approximate_adjusted_volume_market_center_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + approximate_adjusted_volume_market_center_message::tail_capacity };
}
}
