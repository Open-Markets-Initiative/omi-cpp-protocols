#pragma once

#include "../NewOrderCrossMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

class new_order_cross_message_group_writer;
class new_order_cross_message_cross_sides_groups_builder;
class new_order_cross_message_after_cross_sides;
class new_order_cross_message_after_desk_id;

class new_order_cross_message_cross_sides_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_binaryentrypoint::group_size_encoding* header_;
    uint16_t count_ = 0;

public:
    new_order_cross_message_cross_sides_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_binaryentrypoint::group_size_encoding) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_binaryentrypoint::group_size_encoding*>(pos_);
        header_->block_length.set(sizeof(new_order_cross_message_cross_sides_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_binaryentrypoint::group_size_encoding);
    }

    new_order_cross_message_cross_sides_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_binaryentrypoint::group_size_encoding* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    new_order_cross_message_cross_sides_groups_builder& side(sbe_binaryentrypoint::side::enum_type v) {
        if (pos_ + sizeof(new_order_cross_message_cross_sides_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<new_order_cross_message_cross_sides_groups_entry*>(pos_);
        entry->side.set(v);
        return *this;
    }

    new_order_cross_message_cross_sides_groups_builder& offset_1_padding_1(std::span<const std::uint8_t> v) {
        if (pos_ + sizeof(new_order_cross_message_cross_sides_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<new_order_cross_message_cross_sides_groups_entry*>(pos_);
        entry->offset_1_padding_1.set(v);
        return *this;
    }

    new_order_cross_message_cross_sides_groups_builder& account(typename sbe_binaryentrypoint::account::result_type v) {
        if (pos_ + sizeof(new_order_cross_message_cross_sides_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<new_order_cross_message_cross_sides_groups_entry*>(pos_);
        entry->account.set(v);
        return *this;
    }

    new_order_cross_message_cross_sides_groups_builder& entering_firm_optional(typename sbe_binaryentrypoint::entering_firm_optional::result_type v) {
        if (pos_ + sizeof(new_order_cross_message_cross_sides_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<new_order_cross_message_cross_sides_groups_entry*>(pos_);
        entry->entering_firm_optional.set(v);
        return *this;
    }

    new_order_cross_message_cross_sides_groups_builder& clordid(std::uint64_t v) {
        if (pos_ + sizeof(new_order_cross_message_cross_sides_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<new_order_cross_message_cross_sides_groups_entry*>(pos_);
        entry->clordid.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    new_order_cross_message_after_cross_sides end_cross_sides();
};

class new_order_cross_message_after_cross_sides {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    new_order_cross_message_after_cross_sides(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    new_order_cross_message_after_desk_id desk_id(std::string_view v);
};

class new_order_cross_message_after_desk_id {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    new_order_cross_message_after_desk_id(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> memo_and_finish(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* final_pos = pos_ + sizeof(uint32_t) + v.size();
        reinterpret_cast<sbe_binaryentrypoint::simple_open_framing_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(final_pos - msg_start_));
        return { msg_start_, static_cast<size_t>(final_pos - msg_start_) };
    }
};

class new_order_cross_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    new_order_cross_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    new_order_cross_message_cross_sides_groups_builder start_cross_sides() {
        return { msg_start_, pos_, end_ };
    }
};

inline new_order_cross_message_after_cross_sides new_order_cross_message_cross_sides_groups_builder::end_cross_sides() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline new_order_cross_message_after_desk_id new_order_cross_message_after_cross_sides::desk_id(std::string_view v) {
    if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
    *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
    std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
    auto* next_pos = pos_ + sizeof(uint32_t) + v.size();
    return { msg_start_, next_pos, end_ };
}



inline new_order_cross_message_group_writer start_group_write(new_order_cross_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + new_order_cross_message::tail_capacity };
}
}
