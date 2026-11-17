// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/details/ComplexStrategyDefinitionMessageWriter.hpp
#pragma once

#include "../ComplexStrategyDefinitionMessage.hpp"
#include <span>
#include <cstring>
#include <new>
#include <stdexcept>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

class complex_strategy_definition_message_group_writer;
class complex_strategy_definition_message_leg_definition_writer;

class complex_strategy_definition_message_leg_definition_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    complex_strategy_definition_message_leg_definition_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_strategy_definition_message_leg_definition_writer& add_entry(const mach_complextopofmarket::complex_strategy_definition_message_leg_definition_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<mach_complextopofmarket::complex_strategy_definition_message*>(msg_start_)->fields.number_of_legs.set(count_);
        reinterpret_cast<mach_complextopofmarket::mach_packet_header*>(msg_start_)->packet_length.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class complex_strategy_definition_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    complex_strategy_definition_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_strategy_definition_message_leg_definition_writer start_leg_definition() {
        return { msg_start_, pos_, end_ };
    }
};


inline complex_strategy_definition_message_group_writer start_group_write(complex_strategy_definition_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + complex_strategy_definition_message::tail_capacity };
}
}
