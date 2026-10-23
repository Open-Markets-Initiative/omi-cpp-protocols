#pragma once

#include "../MdIncrementalRefreshDailyStatistics.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v8 {

namespace sbe_mdp3 = ::cme::mdp3::v8;

class md_incremental_refresh_daily_statistics_group_writer;
class md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder;

class md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& md_entry_px_optional(typename sbe_mdp3::md_entry_px_optional::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->md_entry_px_optional.set(v);
        return *this;
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& md_entry_size_optional(typename sbe_mdp3::md_entry_size_optional::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->md_entry_size_optional.set(v);
        return *this;
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& security_id(std::int32_t v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->security_id.set(v);
        return *this;
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& rpt_seq(std::uint32_t v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->rpt_seq.set(v);
        return *this;
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& trading_reference_date(typename sbe_mdp3::trading_reference_date::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->trading_reference_date.set(v);
        return *this;
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& settl_price_type(std::uint8_t v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->settl_price_type.set(v);
        return *this;
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& md_update_action(sbe_mdp3::md_update_action::enum_type v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->md_update_action.set(v);
        return *this;
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& md_entry_type_daily_statistics(sbe_mdp3::md_entry_type_daily_statistics::enum_type v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->md_entry_type_daily_statistics.set(v);
        return *this;
    }

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder& padding_7(std::span<const std::uint8_t> v) {
        if (pos_ + sizeof(md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry*>(pos_);
        entry->padding_7.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_incremental_refresh_daily_statistics() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_size*>(msg_start_)->set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class md_incremental_refresh_daily_statistics_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_incremental_refresh_daily_statistics_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_builder start_incremental_refresh_daily_statistics() {
        return { msg_start_, pos_, end_ };
    }
};


inline md_incremental_refresh_daily_statistics_group_writer start_group_write(md_incremental_refresh_daily_statistics& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + md_incremental_refresh_daily_statistics::tail_capacity };
}
}
