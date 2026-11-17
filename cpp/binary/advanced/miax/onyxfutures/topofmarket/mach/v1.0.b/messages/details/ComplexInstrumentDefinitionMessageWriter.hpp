// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/details/ComplexInstrumentDefinitionMessageWriter.hpp
#pragma once

#include "../ComplexInstrumentDefinitionMessage.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

class complex_instrument_definition_message_group_writer;
class complex_instrument_definition_message_instrument_leg_writer;

class complex_instrument_definition_message_instrument_leg_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    complex_instrument_definition_message_instrument_leg_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_instrument_definition_message_instrument_leg_writer& add_entry(const mach_topofmarket::complex_instrument_definition_message_instrument_leg_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<mach_topofmarket::complex_instrument_definition_message*>(msg_start_)->fields.number_of_legs.set(count_);
        reinterpret_cast<mach_topofmarket::mach_packet_header*>(msg_start_)->packet_length.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class complex_instrument_definition_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    complex_instrument_definition_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_instrument_definition_message_instrument_leg_writer start_instrument_leg() {
        return { msg_start_, pos_, end_ };
    }
};


inline complex_instrument_definition_message_group_writer start_group_write(complex_instrument_definition_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + complex_instrument_definition_message::tail_capacity };
}
}
