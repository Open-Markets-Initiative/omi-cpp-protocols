#pragma once

#include "../SnapshotFullRefreshOrdersMbO71Message.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_7;

class snapshot_full_refresh_orders_mb_o_71_message_group_writer;
class snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder;

class snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_binaryumdf::group_size_encoding* header_;
    uint16_t count_ = 0;

public:
    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_binaryumdf::group_size_encoding) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_binaryumdf::group_size_encoding*>(pos_);
        header_->block_length.set(sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_binaryumdf::group_size_encoding);
    }

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_binaryumdf::group_size_encoding* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder& md_corporate_offset_price_optional(typename sbe_binaryumdf::md_corporate_offset_price_optional::result_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        entry->md_corporate_offset_price_optional.set(v);
        return *this;
    }

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder& md_entry_size_quantity(std::int64_t v) {
        if (pos_ + sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        entry->md_entry_size_quantity.set(v);
        return *this;
    }

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder& md_entry_position_no(std::uint32_t v) {
        if (pos_ + sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        entry->md_entry_position_no.set(v);
        return *this;
    }

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder& entering_firm(typename sbe_binaryumdf::entering_firm::result_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        entry->entering_firm.set(v);
        return *this;
    }

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder& md_insert_timestamp(typename sbe_binaryumdf::md_insert_timestamp::result_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        entry->md_insert_timestamp.set(v);
        return *this;
    }

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder& secondary_order_id(std::uint64_t v) {
        if (pos_ + sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        entry->secondary_order_id.set(v);
        return *this;
    }

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder& md_entry_type(sbe_binaryumdf::md_entry_type::enum_type v) {
        if (pos_ + sizeof(snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry*>(pos_);
        entry->md_entry_type.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_no_m_d_entries() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_binaryumdf::framing_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class snapshot_full_refresh_orders_mb_o_71_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    snapshot_full_refresh_orders_mb_o_71_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_builder start_no_m_d_entries() {
        return { msg_start_, pos_, end_ };
    }
};


inline snapshot_full_refresh_orders_mb_o_71_message_group_writer start_group_write(snapshot_full_refresh_orders_mb_o_71_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + snapshot_full_refresh_orders_mb_o_71_message::tail_capacity };
}
}
