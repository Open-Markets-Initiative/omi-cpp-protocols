#pragma once

#include "../CollateralMarketValue.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class collateral_market_value_group_writer;
class collateral_market_value_groups_builder;

class collateral_market_value_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    collateral_market_value_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(collateral_market_value_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    collateral_market_value_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    collateral_market_value_groups_builder& underlying_security_alt_id(std::string_view v) {
        if (pos_ + sizeof(collateral_market_value_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<collateral_market_value_groups_entry*>(pos_);
        entry->underlying_security_alt_id.set(v);
        return *this;
    }

    collateral_market_value_groups_builder& underlying_security_alt_id_source(sbe_mdp3::underlying_security_alt_id_source::enum_type v) {
        if (pos_ + sizeof(collateral_market_value_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<collateral_market_value_groups_entry*>(pos_);
        entry->underlying_security_alt_id_source.set(v);
        return *this;
    }

    collateral_market_value_groups_builder& collateral_market_price(std::int64_t v) {
        if (pos_ + sizeof(collateral_market_value_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<collateral_market_value_groups_entry*>(pos_);
        entry->collateral_market_price.set(v);
        return *this;
    }

    collateral_market_value_groups_builder& dirty_price(std::int64_t v) {
        if (pos_ + sizeof(collateral_market_value_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<collateral_market_value_groups_entry*>(pos_);
        entry->dirty_price.set(v);
        return *this;
    }

    collateral_market_value_groups_builder& underlying_instrument_guid(std::uint64_t v) {
        if (pos_ + sizeof(collateral_market_value_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<collateral_market_value_groups_entry*>(pos_);
        entry->underlying_instrument_guid.set(v);
        return *this;
    }

    collateral_market_value_groups_builder& md_stream_id(sbe_mdp3::md_stream_id::enum_type v) {
        if (pos_ + sizeof(collateral_market_value_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<collateral_market_value_groups_entry*>(pos_);
        entry->md_stream_id.set(v);
        return *this;
    }

    collateral_market_value_groups_builder& padding_2(std::span<const std::uint8_t> v) {
        if (pos_ + sizeof(collateral_market_value_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<collateral_market_value_groups_entry*>(pos_);
        entry->padding_2.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_groups() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class collateral_market_value_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    collateral_market_value_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    collateral_market_value_groups_builder start_groups() {
        return { msg_start_, pos_, end_ };
    }
};


inline collateral_market_value_group_writer start_group_write(collateral_market_value& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + collateral_market_value::tail_capacity };
}
}
