#pragma once

#include "QuoteRequestWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

class quote_request_related_sym_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    quote_request_related_sym_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const quote_request_related_sym_groups_entry& entry() const {
        return *reinterpret_cast<const quote_request_related_sym_groups_entry*>(pos_);
    }

    std::string_view symbol() const {
        auto* entry = reinterpret_cast<const quote_request_related_sym_groups_entry*>(pos_);
        return entry->symbol.get().value();
    }

    std::int32_t security_id() const {
        auto* entry = reinterpret_cast<const quote_request_related_sym_groups_entry*>(pos_);
        return entry->security_id.get().value();
    }

    std::optional<std::int32_t> order_qty() const {
        auto* entry = reinterpret_cast<const quote_request_related_sym_groups_entry*>(pos_);
        return entry->order_qty.get();
    }

    std::int8_t quote_type() const {
        auto* entry = reinterpret_cast<const quote_request_related_sym_groups_entry*>(pos_);
        return entry->quote_type.get().value();
    }

    std::optional<std::int8_t> side() const {
        auto* entry = reinterpret_cast<const quote_request_related_sym_groups_entry*>(pos_);
        return entry->side.get();
    }

    std::array<std::uint8_t, 2> padding_2() const {
        auto* entry = reinterpret_cast<const quote_request_related_sym_groups_entry*>(pos_);
        return entry->padding_2.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class quote_request_related_sym_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    quote_request_related_sym_groups_reader(const std::byte* data, const std::byte* end)
        : end_(end) {
        if (data + sizeof(sbe_mdp3::group_size) > end_)
            throw std::runtime_error("buffer overrun reading group header");
        auto* hdr = reinterpret_cast<const sbe_mdp3::group_size*>(data);
        block_length_ = hdr->block_length.get().value();
        count_ = hdr->num_in_group.get().value();
        pos_ = data + sizeof(sbe_mdp3::group_size);
        index_ = 0;
    }

    uint16_t count() const { return count_; }

    bool has_next() const { return index_ < count_; }

    quote_request_related_sym_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        quote_request_related_sym_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline quote_request_related_sym_groups_reader read_related_sym(const quote_request& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
