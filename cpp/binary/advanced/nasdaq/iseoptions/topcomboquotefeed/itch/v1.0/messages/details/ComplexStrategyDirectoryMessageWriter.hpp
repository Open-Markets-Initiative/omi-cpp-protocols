#pragma once

#include "../ComplexStrategyDirectoryMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

namespace itch_topcomboquotefeed = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

class complex_strategy_directory_message_group_writer;
class complex_strategy_directory_message_leg_information_writer;

class complex_strategy_directory_message_leg_information_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    uint8_t count_ = 0;

public:
    complex_strategy_directory_message_leg_information_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_strategy_directory_message_leg_information_writer& add_entry(const itch_topcomboquotefeed::complex_strategy_directory_message_leg_information_entry& entry) {
        if (pos_ + sizeof(entry) > end_)
            throw std::runtime_error("buffer overrun writing external-count group entry");
        std::memcpy(pos_, &entry, sizeof(entry));
        pos_ += sizeof(entry);
        ++count_;
        return *this;
    }

    std::span<std::byte> finish() {
        reinterpret_cast<itch_topcomboquotefeed::complex_strategy_directory_message*>(msg_start_)->fields.number_of_legs.set(count_);
        reinterpret_cast<itch_topcomboquotefeed::message_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_ - 2));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class complex_strategy_directory_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    complex_strategy_directory_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    complex_strategy_directory_message_leg_information_writer start_leg_information() {
        return { msg_start_, pos_, end_ };
    }
};


inline complex_strategy_directory_message_group_writer start_group_write(complex_strategy_directory_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + complex_strategy_directory_message::tail_capacity };
}
}
