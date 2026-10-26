#pragma once

#include "../MdIncrementalRefreshSessionStatisticsLongQty.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class md_incremental_refresh_session_statistics_long_qty_group_writer;
class md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder;

class md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder& md_entry_px_ex(std::int64_t v) {
        if (pos_ + sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry*>(pos_);
        entry->md_entry_px_ex.set(v);
        return *this;
    }

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder& md_entry_size_optional(typename sbe_mdp3::md_entry_size_optional::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry*>(pos_);
        entry->md_entry_size_optional.set(v);
        return *this;
    }

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder& security_id(std::int32_t v) {
        if (pos_ + sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry*>(pos_);
        entry->security_id.set(v);
        return *this;
    }

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder& rpt_seq(std::uint32_t v) {
        if (pos_ + sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry*>(pos_);
        entry->rpt_seq.set(v);
        return *this;
    }

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder& open_close_settl_flag(sbe_mdp3::open_close_settl_flag::enum_type v) {
        if (pos_ + sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry*>(pos_);
        entry->open_close_settl_flag.set(v);
        return *this;
    }

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder& md_update_action(sbe_mdp3::md_update_action::enum_type v) {
        if (pos_ + sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry*>(pos_);
        entry->md_update_action.set(v);
        return *this;
    }

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder& md_entry_type_statistics(sbe_mdp3::md_entry_type_statistics::enum_type v) {
        if (pos_ + sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry*>(pos_);
        entry->md_entry_type_statistics.set(v);
        return *this;
    }

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder& padding_5(std::span<const std::uint8_t> v) {
        if (pos_ + sizeof(md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_entry*>(pos_);
        entry->padding_5.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_incremental_refresh_session_statistics_long() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class md_incremental_refresh_session_statistics_long_qty_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_incremental_refresh_session_statistics_long_qty_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_incremental_refresh_session_statistics_long_qty_incremental_refresh_session_statistics_long_groups_builder start_incremental_refresh_session_statistics_long() {
        return { msg_start_, pos_, end_ };
    }
};


inline md_incremental_refresh_session_statistics_long_qty_group_writer start_group_write(md_incremental_refresh_session_statistics_long_qty& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + md_incremental_refresh_session_statistics_long_qty::tail_capacity };
}
}
