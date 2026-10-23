#pragma once

#include "../MdIncrementalRefreshBookLongQty.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class md_incremental_refresh_book_long_qty_group_writer;
class md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder;
class md_incremental_refresh_book_long_qty_after_incremental_refresh_book_long;
class md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder;

class md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& md_entry_px_optional_ex(typename sbe_mdp3::md_entry_px_optional_ex::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->md_entry_px_optional_ex.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& md_entry_size_optional(typename sbe_mdp3::md_entry_size_optional::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->md_entry_size_optional.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& security_id(std::int32_t v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->security_id.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& rpt_seq(std::uint32_t v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->rpt_seq.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& number_of_orders_optional(typename sbe_mdp3::number_of_orders_optional::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->number_of_orders_optional.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& md_price_level(std::uint8_t v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->md_price_level.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& md_update_action(sbe_mdp3::md_update_action::enum_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->md_update_action.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& md_entry_type_book(sbe_mdp3::md_entry_type_book::enum_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->md_entry_type_book.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder& padding_1(std::span<const std::uint8_t> v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry*>(pos_);
        entry->padding_1.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_incremental_refresh_book_long_qty_after_incremental_refresh_book_long end_incremental_refresh_book_long();
};

class md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size_8_byte* header_;
    uint16_t count_ = 0;

public:
    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size_8_byte) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size_8_byte*>(pos_);
        header_->block_length.set(sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size_8_byte);
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size_8_byte* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder& order_id(std::uint64_t v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        entry->order_id.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder& md_order_priority_optional(typename sbe_mdp3::md_order_priority_optional::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        entry->md_order_priority_optional.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder& md_display_qty_optional(typename sbe_mdp3::md_display_qty_optional::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        entry->md_display_qty_optional.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder& reference_id(typename sbe_mdp3::reference_id::result_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        entry->reference_id.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder& order_update_action(sbe_mdp3::order_update_action::enum_type v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        entry->order_update_action.set(v);
        return *this;
    }

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder& padding_2(std::span<const std::uint8_t> v) {
        if (pos_ + sizeof(md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry*>(pos_);
        entry->padding_2.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_incremental_refresh_book_long_order_id() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_size*>(msg_start_)->set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class md_incremental_refresh_book_long_qty_after_incremental_refresh_book_long {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_incremental_refresh_book_long_qty_after_incremental_refresh_book_long(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_builder start_incremental_refresh_book_long_order_id() {
        return { msg_start_, pos_, end_ };
    }
};

class md_incremental_refresh_book_long_qty_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_incremental_refresh_book_long_qty_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder start_incremental_refresh_book_long() {
        return { msg_start_, pos_, end_ };
    }
};

inline md_incremental_refresh_book_long_qty_after_incremental_refresh_book_long md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_builder::end_incremental_refresh_book_long() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}



inline md_incremental_refresh_book_long_qty_group_writer start_group_write(md_incremental_refresh_book_long_qty& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + md_incremental_refresh_book_long_qty::tail_capacity };
}
}
