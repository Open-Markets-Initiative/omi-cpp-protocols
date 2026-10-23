#pragma once

#include "MdIncrementalRefreshBookLongQtyWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry& entry() const {
        return *reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
    }

    std::optional<std::int64_t> md_entry_px_optional_ex() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->md_entry_px_optional_ex.get();
    }

    std::optional<std::uint64_t> md_entry_size_optional() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->md_entry_size_optional.get();
    }

    std::int32_t security_id() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->security_id.get().value();
    }

    std::uint32_t rpt_seq() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->rpt_seq.get().value();
    }

    std::optional<std::int32_t> number_of_orders_optional() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->number_of_orders_optional.get();
    }

    std::uint8_t md_price_level() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->md_price_level.get().value();
    }

    sbe_mdp3::md_update_action::enum_type md_update_action() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->md_update_action.get().value();
    }

    sbe_mdp3::md_entry_type_book::enum_type md_entry_type_book() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->md_entry_type_book.get().value();
    }

    std::array<std::uint8_t, 1> padding_1() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        return entry->padding_1.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_reader(const std::byte* data, const std::byte* end)
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

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry& entry() const {
        return *reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
    }

    std::uint64_t order_id() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        return entry->order_id.get().value();
    }

    std::optional<std::uint64_t> md_order_priority_optional() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        return entry->md_order_priority_optional.get();
    }

    std::optional<std::int32_t> md_display_qty_optional() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        return entry->md_display_qty_optional.get();
    }

    std::optional<std::uint8_t> reference_id() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        return entry->reference_id.get();
    }

    sbe_mdp3::order_update_action::enum_type order_update_action() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        return entry->order_update_action.get().value();
    }

    std::array<std::uint8_t, 2> padding_2() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        return entry->padding_2.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_reader(const std::byte* data, const std::byte* end)
        : end_(end) {
        if (data + sizeof(sbe_mdp3::group_size_8_byte) > end_)
            throw std::runtime_error("buffer overrun reading group header");
        auto* hdr = reinterpret_cast<const sbe_mdp3::group_size_8_byte*>(data);
        block_length_ = hdr->block_length.get().value();
        count_ = hdr->num_in_group.get().value();
        pos_ = data + sizeof(sbe_mdp3::group_size_8_byte);
        index_ = 0;
    }

    uint16_t count() const { return count_; }

    bool has_next() const { return index_ < count_; }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_reader read_incremental_refresh_book_long(const md_incremental_refresh_book_long_qty& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_reader read_incremental_refresh_book_long_order_id(const std::byte* pos, const md_incremental_refresh_book_long_qty& msg) {
    return { pos, msg.tail_end() };
}

}
