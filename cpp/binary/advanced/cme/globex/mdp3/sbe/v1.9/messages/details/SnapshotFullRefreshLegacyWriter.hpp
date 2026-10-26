#pragma once

#include "../SnapshotFullRefreshLegacy.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

class snapshot_full_refresh_legacy_group_writer;
class snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder;

class snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder& md_entry_px_optional_ex(typename sbe_mdp3::md_entry_px_optional_ex::result_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        entry->md_entry_px_optional_ex.set(v);
        return *this;
    }

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder& md_entry_size_short_optional(typename sbe_mdp3::md_entry_size_short_optional::result_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        entry->md_entry_size_short_optional.set(v);
        return *this;
    }

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder& number_of_orders_optional(typename sbe_mdp3::number_of_orders_optional::result_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        entry->number_of_orders_optional.set(v);
        return *this;
    }

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder& md_price_level_optional(typename sbe_mdp3::md_price_level_optional::result_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        entry->md_price_level_optional.set(v);
        return *this;
    }

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder& trading_reference_date(typename sbe_mdp3::trading_reference_date::result_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        entry->trading_reference_date.set(v);
        return *this;
    }

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder& open_close_settl_flag(sbe_mdp3::open_close_settl_flag::enum_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        entry->open_close_settl_flag.set(v);
        return *this;
    }

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder& settl_price_type(std::uint8_t v) {
        if (pos_ + sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        entry->settl_price_type.set(v);
        return *this;
    }

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder& md_entry_type(sbe_mdp3::md_entry_type::enum_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_legacy_snapshot_full_refresh_groups_entry*>(pos_);
        entry->md_entry_type.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_snapshot_full_refresh() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class snapshot_full_refresh_legacy_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    snapshot_full_refresh_legacy_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    snapshot_full_refresh_legacy_snapshot_full_refresh_groups_builder start_snapshot_full_refresh() {
        return { msg_start_, pos_, end_ };
    }
};


inline snapshot_full_refresh_legacy_group_writer start_group_write(snapshot_full_refresh_legacy& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + snapshot_full_refresh_legacy::tail_capacity };
}
}
