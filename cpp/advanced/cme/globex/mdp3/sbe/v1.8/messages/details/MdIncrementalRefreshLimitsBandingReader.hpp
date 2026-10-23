#pragma once

#include "MdIncrementalRefreshLimitsBandingWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

class md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry& entry() const {
        return *reinterpret_cast<const md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry*>(pos_);
    }

    std::optional<std::int64_t> high_limit_price() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry*>(pos_);
        return entry->high_limit_price.get();
    }

    std::optional<std::int64_t> low_limit_price() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry*>(pos_);
        return entry->low_limit_price.get();
    }

    std::optional<std::int64_t> max_price_variation() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry*>(pos_);
        return entry->max_price_variation.get();
    }

    std::int32_t security_id() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry*>(pos_);
        return entry->security_id.get().value();
    }

    std::uint32_t rpt_seq() const {
        auto* entry = reinterpret_cast<const md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry*>(pos_);
        return entry->rpt_seq.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_reader(const std::byte* data, const std::byte* end)
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

    md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_reader read_incremental_refresh_limits_banding(const md_incremental_refresh_limits_banding& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
