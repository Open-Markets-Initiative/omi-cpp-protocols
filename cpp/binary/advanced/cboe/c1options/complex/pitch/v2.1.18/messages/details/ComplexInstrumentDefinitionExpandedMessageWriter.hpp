#pragma once

#include "../ComplexInstrumentDefinitionExpandedMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

class complex_instrument_definition_expanded_message_group_writer;
class complex_instrument_definition_expanded_message_complex_instrument_leg_writer;

class complex_instrument_definition_expanded_message_complex_instrument_leg_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    complex_instrument_definition_expanded_message_complex_instrument_leg_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_instrument_definition_expanded_message_complex_instrument_leg_writer& add_entry(const pitch_complex::complex_instrument_definition_expanded_message_complex_instrument_leg_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<pitch_complex::complex_instrument_definition_expanded_message*>(msg_start_)->fields.leg_count.set(count_);
        reinterpret_cast<pitch_complex::message_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class complex_instrument_definition_expanded_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    complex_instrument_definition_expanded_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_instrument_definition_expanded_message_complex_instrument_leg_writer start_complex_instrument_leg() {
        return { msg_start_, pos_, end_ };
    }
};


inline complex_instrument_definition_expanded_message_group_writer start_group_write(complex_instrument_definition_expanded_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + complex_instrument_definition_expanded_message::tail_capacity };
}
}
