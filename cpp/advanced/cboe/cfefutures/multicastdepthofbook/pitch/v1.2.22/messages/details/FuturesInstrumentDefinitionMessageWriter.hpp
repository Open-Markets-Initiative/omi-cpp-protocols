#pragma once

#include "../FuturesInstrumentDefinitionMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

class futures_instrument_definition_message_group_writer;
class futures_instrument_definition_message_future_leg_writer;

class futures_instrument_definition_message_future_leg_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    futures_instrument_definition_message_future_leg_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    futures_instrument_definition_message_future_leg_writer& add_entry(const pitch_multicastdepthofbook::futures_instrument_definition_message_future_leg_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<pitch_multicastdepthofbook::futures_instrument_definition_message*>(msg_start_)->fields.leg_count.set(count_);
        reinterpret_cast<pitch_multicastdepthofbook::message_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class futures_instrument_definition_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    futures_instrument_definition_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    futures_instrument_definition_message_future_leg_writer start_future_leg() {
        return { msg_start_, pos_, end_ };
    }
};


inline futures_instrument_definition_message_group_writer start_group_write(futures_instrument_definition_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + futures_instrument_definition_message::tail_capacity };
}
}
