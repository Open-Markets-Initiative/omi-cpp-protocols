#pragma once

#include "CollateralMarketValueWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class collateral_market_value_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    collateral_market_value_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const collateral_market_value_groups_entry& entry() const {
        return *reinterpret_cast<const collateral_market_value_groups_entry*>(pos_);
    }

    std::string_view underlying_security_alt_id() const {
        auto* entry = reinterpret_cast<const collateral_market_value_groups_entry*>(pos_);
        return entry->underlying_security_alt_id.get().value();
    }

    sbe_mdp3::underlying_security_alt_id_source::enum_type underlying_security_alt_id_source() const {
        auto* entry = reinterpret_cast<const collateral_market_value_groups_entry*>(pos_);
        return entry->underlying_security_alt_id_source.get().value();
    }

    std::int64_t collateral_market_price() const {
        auto* entry = reinterpret_cast<const collateral_market_value_groups_entry*>(pos_);
        return entry->collateral_market_price.get().value();
    }

    std::int64_t dirty_price() const {
        auto* entry = reinterpret_cast<const collateral_market_value_groups_entry*>(pos_);
        return entry->dirty_price.get().value();
    }

    std::uint64_t underlying_instrument_guid() const {
        auto* entry = reinterpret_cast<const collateral_market_value_groups_entry*>(pos_);
        return entry->underlying_instrument_guid.get().value();
    }

    sbe_mdp3::md_stream_id::enum_type md_stream_id() const {
        auto* entry = reinterpret_cast<const collateral_market_value_groups_entry*>(pos_);
        return entry->md_stream_id.get().value();
    }

    std::array<std::uint8_t, 2> padding_2() const {
        auto* entry = reinterpret_cast<const collateral_market_value_groups_entry*>(pos_);
        return entry->padding_2.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class collateral_market_value_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    collateral_market_value_groups_reader(const std::byte* data, const std::byte* end)
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

    collateral_market_value_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        collateral_market_value_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline collateral_market_value_groups_reader read_groups(const collateral_market_value& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

}
