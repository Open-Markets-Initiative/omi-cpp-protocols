#pragma once

#include "../ComplexSymbolDefinitionMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

class complex_symbol_definition_message_group_writer;
class complex_symbol_definition_message_leg_definition_writer;

class complex_symbol_definition_message_leg_definition_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint16_t count_ = 0;

public:
    complex_symbol_definition_message_leg_definition_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_symbol_definition_message_leg_definition_writer& add_entry(const xdp_complexfeed::complex_symbol_definition_message_leg_definition_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<xdp_complexfeed::complex_symbol_definition_message*>(msg_start_)->fields.no_of_legs.set(count_);
        reinterpret_cast<xdp_complexfeed::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class complex_symbol_definition_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    complex_symbol_definition_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_symbol_definition_message_leg_definition_writer start_leg_definition() {
        return { msg_start_, pos_, end_ };
    }
};


inline complex_symbol_definition_message_group_writer start_group_write(complex_symbol_definition_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + complex_symbol_definition_message::tail_capacity };
}
}
