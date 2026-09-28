#pragma once

#include "SnapshotFullRefreshOrdersMbO71MessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_9;

class snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    std::optional<std::int64_t> md_corporate_offset_price_optional() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        return entry->md_corporate_offset_price_optional.get();
    }

    std::int64_t md_entry_size_quantity() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        return entry->md_entry_size_quantity.get().value();
    }

    std::uint32_t md_entry_position_no() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        return entry->md_entry_position_no.get().value();
    }

    std::optional<std::uint32_t> entering_firm() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        return entry->entering_firm.get();
    }

    std::optional<std::uint64_t> md_insert_timestamp() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        return entry->md_insert_timestamp.get();
    }

    std::uint64_t secondary_order_id() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        return entry->secondary_order_id.get().value();
    }

    sbe_binaryumdf::md_entry_type::enum_type md_entry_type() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        return entry->md_entry_type.get().value();
    }

    std::uint8_t match_event_indicator_optional() const {
        auto* entry = reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        return entry->match_event_indicator_optional.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_reader(const std::byte* data, const std::byte* end)
        : end_(end) {
        if (data + sizeof(sbe_binaryumdf::group_size_encoding) > end_)
            throw std::runtime_error("buffer overrun reading group header");
        auto* hdr = reinterpret_cast<const sbe_binaryumdf::group_size_encoding*>(data);
        block_length_ = hdr->block_length.get().value();
        count_ = hdr->num_in_group.get().value();
        pos_ = data + sizeof(sbe_binaryumdf::group_size_encoding);
        index_ = 0;
    }

    uint16_t count() const { return count_; }

    bool has_next() const { return index_ < count_; }

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_reader read_no_m_d_entries(const snapshot_full_refresh_orders_mb_o_71_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
