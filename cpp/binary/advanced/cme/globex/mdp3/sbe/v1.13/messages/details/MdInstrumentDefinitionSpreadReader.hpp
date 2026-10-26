#pragma once

#include "MdInstrumentDefinitionSpreadWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class md_instrument_definition_spread_events_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_spread_events_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_spread_events_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_spread_events_groups_entry*>(pos_);
    }

    sbe_mdp3::event_type::enum_type event_type() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_events_groups_entry*>(pos_);
        return entry->event_type.get().value();
    }

    std::uint64_t event_time() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_events_groups_entry*>(pos_);
        return entry->event_time.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_spread_events_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_spread_events_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_spread_events_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_spread_events_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_spread_feed_types_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_spread_feed_types_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_spread_feed_types_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_spread_feed_types_groups_entry*>(pos_);
    }

    std::string_view md_feed_type() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_feed_types_groups_entry*>(pos_);
        return entry->md_feed_type.get().value();
    }

    std::int8_t market_depth() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_feed_types_groups_entry*>(pos_);
        return entry->market_depth.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_spread_feed_types_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_spread_feed_types_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_spread_feed_types_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_spread_feed_types_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_spread_inst_attrib_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_spread_inst_attrib_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_spread_inst_attrib_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_spread_inst_attrib_groups_entry*>(pos_);
    }

    std::uint32_t inst_attrib_value() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_inst_attrib_groups_entry*>(pos_);
        return entry->inst_attrib_value.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_spread_inst_attrib_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_spread_inst_attrib_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_spread_inst_attrib_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_spread_inst_attrib_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_spread_lot_type_rules_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_spread_lot_type_rules_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_spread_lot_type_rules_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_spread_lot_type_rules_groups_entry*>(pos_);
    }

    std::int8_t lot_type() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_lot_type_rules_groups_entry*>(pos_);
        return entry->lot_type.get().value();
    }

    std::optional<std::int32_t> min_lot_size_decimal_qty() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_lot_type_rules_groups_entry*>(pos_);
        return entry->min_lot_size_decimal_qty.get();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_spread_lot_type_rules_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_spread_lot_type_rules_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_spread_lot_type_rules_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_spread_lot_type_rules_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_spread_legs_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_spread_legs_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_spread_legs_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_spread_legs_groups_entry*>(pos_);
    }

    std::int32_t leg_security_id() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_legs_groups_entry*>(pos_);
        return entry->leg_security_id.get().value();
    }

    sbe_mdp3::leg_side::enum_type leg_side() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_legs_groups_entry*>(pos_);
        return entry->leg_side.get().value();
    }

    std::int8_t leg_ratio_qty() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_legs_groups_entry*>(pos_);
        return entry->leg_ratio_qty.get().value();
    }

    std::optional<std::int64_t> leg_price() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_legs_groups_entry*>(pos_);
        return entry->leg_price.get();
    }

    std::optional<std::int32_t> leg_option_delta() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_spread_legs_groups_entry*>(pos_);
        return entry->leg_option_delta.get();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_spread_legs_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_spread_legs_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_spread_legs_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_spread_legs_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline md_instrument_definition_spread_events_groups_reader read_events(const md_instrument_definition_spread& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline md_instrument_definition_spread_feed_types_groups_reader read_feed_types(const std::byte* pos, const md_instrument_definition_spread& msg) {
    return { pos, msg.tail_end() };
}

inline md_instrument_definition_spread_inst_attrib_groups_reader read_inst_attrib(const std::byte* pos, const md_instrument_definition_spread& msg) {
    return { pos, msg.tail_end() };
}

inline md_instrument_definition_spread_lot_type_rules_groups_reader read_lot_type_rules(const std::byte* pos, const md_instrument_definition_spread& msg) {
    return { pos, msg.tail_end() };
}

inline md_instrument_definition_spread_legs_groups_reader read_legs(const std::byte* pos, const md_instrument_definition_spread& msg) {
    return { pos, msg.tail_end() };
}

}
