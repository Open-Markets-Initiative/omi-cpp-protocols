#pragma once

#include "SecurityDefinitionRequestMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

class security_definition_request_message_legs_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    security_definition_request_message_legs_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const security_definition_request_message_legs_groups_entry& entry() const {
        return *reinterpret_cast<const security_definition_request_message_legs_groups_entry*>(pos_);
    }

    std::string_view leg_symbol() const {
        auto* entry = reinterpret_cast<const security_definition_request_message_legs_groups_entry*>(pos_);
        return entry->leg_symbol.get().value();
    }

    std::int64_t leg_ratio_qty() const {
        auto* entry = reinterpret_cast<const security_definition_request_message_legs_groups_entry*>(pos_);
        return entry->leg_ratio_qty.get().value();
    }

    sbe_binaryentrypoint::leg_side::enum_type leg_side() const {
        auto* entry = reinterpret_cast<const security_definition_request_message_legs_groups_entry*>(pos_);
        return entry->leg_side.get().value();
    }

    std::array<std::uint8_t, 1> padding_1() const {
        auto* entry = reinterpret_cast<const security_definition_request_message_legs_groups_entry*>(pos_);
        return entry->padding_1.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class security_definition_request_message_legs_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    security_definition_request_message_legs_groups_reader(const std::byte* data, const std::byte* end)
        : end_(end) {
        if (data + sizeof(sbe_binaryentrypoint::group_size_encoding) > end_)
            throw std::runtime_error("buffer overrun reading group header");
        auto* hdr = reinterpret_cast<const sbe_binaryentrypoint::group_size_encoding*>(data);
        block_length_ = hdr->block_length.get().value();
        count_ = hdr->num_in_group.get().value();
        pos_ = data + sizeof(sbe_binaryentrypoint::group_size_encoding);
        index_ = 0;
    }

    uint16_t count() const { return count_; }

    bool has_next() const { return index_ < count_; }

    security_definition_request_message_legs_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        security_definition_request_message_legs_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline security_definition_request_message_legs_groups_reader read_legs(const security_definition_request_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
