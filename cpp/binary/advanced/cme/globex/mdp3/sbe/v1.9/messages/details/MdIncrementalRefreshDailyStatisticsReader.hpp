#pragma once

#include "MdIncrementalRefreshDailyStatisticsWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

class md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry& entry() const {
        return *reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
    }

    std::optional<std::int64_t> md_entry_px_optional_ex() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->md_entry_px_optional_ex.get();
    }

    std::optional<std::int32_t> md_entry_size_short_optional() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->md_entry_size_short_optional.get();
    }

    std::int32_t security_id() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->security_id.get().value();
    }

    std::uint32_t rpt_seq() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->rpt_seq.get().value();
    }

    std::optional<std::uint16_t> trading_reference_date() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->trading_reference_date.get();
    }

    std::uint8_t settl_price_type() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->settl_price_type.get().value();
    }

    sbe_mdp3::md_update_action::enum_type md_update_action() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->md_update_action.get().value();
    }

    sbe_mdp3::md_entry_type_daily_statistics::enum_type md_entry_type_daily_statistics() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->md_entry_type_daily_statistics.get().value();
    }

    std::array<std::uint8_t, 7> padding_7() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        return entry->padding_7.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_reader(const std::byte* data, const std::byte* end)
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

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_reader read_incremental_refresh_daily_statistics(const md_incremental_refresh_daily_statistics& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
