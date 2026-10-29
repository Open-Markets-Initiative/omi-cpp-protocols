#pragma once

#include "../SecurityDefinitionRequestMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;

class security_definition_request_message_group_writer;
class security_definition_request_message_legs_groups_builder;

class security_definition_request_message_legs_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_binaryentrypoint::group_size_encoding* header_;
    uint16_t count_ = 0;

public:
    security_definition_request_message_legs_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_binaryentrypoint::group_size_encoding) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_binaryentrypoint::group_size_encoding*>(pos_);
        header_->block_length.set(sizeof(security_definition_request_message_legs_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_binaryentrypoint::group_size_encoding);
    }

    security_definition_request_message_legs_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_binaryentrypoint::group_size_encoding* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    security_definition_request_message_legs_groups_builder& leg_symbol(std::string_view v) {
        if (pos_ + sizeof(security_definition_request_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_request_message_legs_groups_entry*>(pos_);
        entry->leg_symbol.set(v);
        return *this;
    }

    security_definition_request_message_legs_groups_builder& leg_ratio_qty(std::int64_t v) {
        if (pos_ + sizeof(security_definition_request_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_request_message_legs_groups_entry*>(pos_);
        entry->leg_ratio_qty.set(v);
        return *this;
    }

    security_definition_request_message_legs_groups_builder& leg_side(sbe_binaryentrypoint::leg_side::enum_type v) {
        if (pos_ + sizeof(security_definition_request_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_request_message_legs_groups_entry*>(pos_);
        entry->leg_side.set(v);
        return *this;
    }

    security_definition_request_message_legs_groups_builder& padding_1(std::span<const std::uint8_t> v) {
        if (pos_ + sizeof(security_definition_request_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_request_message_legs_groups_entry*>(pos_);
        entry->padding_1.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_legs() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_binaryentrypoint::simple_open_framing_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class security_definition_request_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_request_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_request_message_legs_groups_builder start_legs() {
        return { msg_start_, pos_, end_ };
    }
};


inline security_definition_request_message_group_writer start_group_write(security_definition_request_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + security_definition_request_message::tail_capacity };
}
}
