#pragma once

#include "../QuoteRequest.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class quote_request_group_writer;
class quote_request_related_sym_groups_builder;

class quote_request_related_sym_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    quote_request_related_sym_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(quote_request_related_sym_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    quote_request_related_sym_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    quote_request_related_sym_groups_builder& symbol(std::string_view v) {
        if (pos_ + sizeof(quote_request_related_sym_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<quote_request_related_sym_groups_entry*>(pos_);
        entry->symbol.set(v);
        return *this;
    }

    quote_request_related_sym_groups_builder& security_id(std::int32_t v) {
        if (pos_ + sizeof(quote_request_related_sym_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<quote_request_related_sym_groups_entry*>(pos_);
        entry->security_id.set(v);
        return *this;
    }

    quote_request_related_sym_groups_builder& order_qty(typename sbe_mdp3::order_qty::result_type v) {
        if (pos_ + sizeof(quote_request_related_sym_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<quote_request_related_sym_groups_entry*>(pos_);
        entry->order_qty.set(v);
        return *this;
    }

    quote_request_related_sym_groups_builder& quote_type(std::int8_t v) {
        if (pos_ + sizeof(quote_request_related_sym_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<quote_request_related_sym_groups_entry*>(pos_);
        entry->quote_type.set(v);
        return *this;
    }

    quote_request_related_sym_groups_builder& side_optional(typename sbe_mdp3::side_optional::result_type v) {
        if (pos_ + sizeof(quote_request_related_sym_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<quote_request_related_sym_groups_entry*>(pos_);
        entry->side_optional.set(v);
        return *this;
    }

    quote_request_related_sym_groups_builder& padding_2(std::span<const std::uint8_t> v) {
        if (pos_ + sizeof(quote_request_related_sym_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<quote_request_related_sym_groups_entry*>(pos_);
        entry->padding_2.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_related_sym() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_size*>(msg_start_)->set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class quote_request_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    quote_request_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    quote_request_related_sym_groups_builder start_related_sym() {
        return { msg_start_, pos_, end_ };
    }
};


inline quote_request_group_writer start_group_write(quote_request& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + quote_request::tail_capacity };
}
}
