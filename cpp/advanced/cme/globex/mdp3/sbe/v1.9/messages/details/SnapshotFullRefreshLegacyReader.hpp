#pragma once

#include "SnapshotFullRefreshLegacyWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

class snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry& entry() const {
        return *reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
    }

    std::optional<std::int64_t> md_entry_px_optional_ex() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        return entry->md_entry_px_optional_ex.get();
    }

    std::optional<std::int32_t> md_entry_size_short_optional() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        return entry->md_entry_size_short_optional.get();
    }

    std::optional<std::int32_t> number_of_orders_optional() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        return entry->number_of_orders_optional.get();
    }

    std::optional<std::int8_t> md_price_level_optional() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        return entry->md_price_level_optional.get();
    }

    std::optional<std::uint16_t> trading_reference_date() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        return entry->trading_reference_date.get();
    }

    sbe_mdp3::open_close_settl_flag::enum_type open_close_settl_flag() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        return entry->open_close_settl_flag.get().value();
    }

    std::uint8_t settl_price_type() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        return entry->settl_price_type.get().value();
    }

    sbe_mdp3::md_entry_type::enum_type md_entry_type() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        return entry->md_entry_type.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class snapshot_full_refresh_legacy_snapshot_full_refresh_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_reader(const std::byte* data, const std::byte* end)
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

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline snapshot_full_refresh_legacy_snapshot_full_refresh_groups_reader read_snapshot_full_refresh(const snapshot_full_refresh_legacy& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
