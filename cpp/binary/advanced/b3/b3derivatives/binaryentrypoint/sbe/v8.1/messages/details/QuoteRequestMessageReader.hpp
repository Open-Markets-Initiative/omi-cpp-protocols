#pragma once

#include "QuoteRequestMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

class quote_request_message_sides_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    quote_request_message_sides_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const quote_request_message_sides_groups_entry& entry() const {
        return *reinterpret_cast<const quote_request_message_sides_groups_entry*>(pos_);
    }

    sbe_binaryentrypoint::side::enum_type side() const {
        auto* entry = reinterpret_cast<const quote_request_message_sides_groups_entry*>(pos_);
        return entry->side.get().value();
    }

    std::optional<std::uint32_t> account() const {
        auto* entry = reinterpret_cast<const quote_request_message_sides_groups_entry*>(pos_);
        return entry->account.get();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class quote_request_message_sides_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    quote_request_message_sides_groups_reader(const std::byte* data, const std::byte* end)
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

    quote_request_message_sides_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        quote_request_message_sides_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline quote_request_message_sides_groups_reader read_sides(const quote_request_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline sbe_var_data read_desk_id(const std::byte* pos, const quote_request_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data read_memo(const std::byte* pos, const quote_request_message& msg) {
    return { pos, msg.tail_end() };
}

}
