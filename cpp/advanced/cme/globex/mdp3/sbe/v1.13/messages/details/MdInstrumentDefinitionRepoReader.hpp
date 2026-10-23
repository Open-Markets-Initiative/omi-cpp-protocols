#pragma once

#include "MdInstrumentDefinitionRepoWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class md_instrument_definition_repo_events_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_repo_events_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_repo_events_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_repo_events_groups_entry*>(pos_);
    }

    sbe_mdp3::event_type::enum_type event_type() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_events_groups_entry*>(pos_);
        return entry->event_type.get().value();
    }

    std::uint64_t event_time() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_events_groups_entry*>(pos_);
        return entry->event_time.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_repo_events_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_repo_events_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_repo_events_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_repo_events_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_repo_feed_types_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_repo_feed_types_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_repo_feed_types_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_repo_feed_types_groups_entry*>(pos_);
    }

    std::string_view md_feed_type() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_feed_types_groups_entry*>(pos_);
        return entry->md_feed_type.get().value();
    }

    std::int8_t market_depth() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_feed_types_groups_entry*>(pos_);
        return entry->market_depth.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_repo_feed_types_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_repo_feed_types_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_repo_feed_types_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_repo_feed_types_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_repo_inst_attrib_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_repo_inst_attrib_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_repo_inst_attrib_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_repo_inst_attrib_groups_entry*>(pos_);
    }

    std::uint32_t inst_attrib_value() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_inst_attrib_groups_entry*>(pos_);
        return entry->inst_attrib_value.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_repo_inst_attrib_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_repo_inst_attrib_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_repo_inst_attrib_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_repo_inst_attrib_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_repo_lot_type_rules_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_repo_lot_type_rules_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_repo_lot_type_rules_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_repo_lot_type_rules_groups_entry*>(pos_);
    }

    std::int8_t lot_type() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_lot_type_rules_groups_entry*>(pos_);
        return entry->lot_type.get().value();
    }

    std::optional<std::int32_t> min_lot_size_decimal_qty() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_lot_type_rules_groups_entry*>(pos_);
        return entry->min_lot_size_decimal_qty.get();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_repo_lot_type_rules_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_repo_lot_type_rules_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_repo_lot_type_rules_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_repo_lot_type_rules_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_repo_repo_underlyings_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_repo_repo_underlyings_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_repo_repo_underlyings_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
    }

    std::string_view underlying_symbol() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_symbol.get().value();
    }

    std::optional<std::int32_t> underlying_security_id_optional() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_security_id_optional.get();
    }

    std::string_view underlying_security_alt_id() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_security_alt_id.get().value();
    }

    sbe_mdp3::underlying_security_alt_id_source::enum_type underlying_security_alt_id_source() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_security_alt_id_source.get().value();
    }

    std::string_view underlying_financial_instrument_full_name() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_financial_instrument_full_name.get().value();
    }

    std::string_view underlying_security_type() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_security_type.get().value();
    }

    std::string_view underlying_country_of_issue() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_country_of_issue.get().value();
    }

    std::string_view underlying_issuer() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_issuer.get().value();
    }

    std::optional<std::uint8_t> underlying_max_life_time() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_max_life_time.get();
    }

    std::optional<std::uint16_t> underlying_min_days_to_maturity() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_min_days_to_maturity.get();
    }

    std::optional<std::uint64_t> underlying_instrument_guid_optional() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_instrument_guid_optional.get();
    }

    std::optional<std::uint16_t> underlying_maturity_date() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        return entry->underlying_maturity_date.get();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_repo_repo_underlyings_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_repo_repo_underlyings_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_repo_repo_underlyings_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_repo_repo_underlyings_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_repo_repo_related_instruments_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_repo_repo_related_instruments_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_repo_repo_related_instruments_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_repo_repo_related_instruments_groups_entry*>(pos_);
    }

    std::int32_t related_security_id() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_related_instruments_groups_entry*>(pos_);
        return entry->related_security_id.get().value();
    }

    std::string_view related_symbol() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_related_instruments_groups_entry*>(pos_);
        return entry->related_symbol.get().value();
    }

    std::optional<std::uint64_t> related_instrument_guid() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_repo_related_instruments_groups_entry*>(pos_);
        return entry->related_instrument_guid.get();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_repo_repo_related_instruments_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_repo_repo_related_instruments_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_repo_repo_related_instruments_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_repo_repo_related_instruments_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class md_instrument_definition_repo_broken_dates_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    md_instrument_definition_repo_broken_dates_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    const md_instrument_definition_repo_broken_dates_groups_entry& entry() const {
        return *reinterpret_cast<const md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
    }

    std::uint64_t broken_date_guid() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
        return entry->broken_date_guid.get().value();
    }

    std::int32_t broken_date_security_id() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
        return entry->broken_date_security_id.get().value();
    }

    std::optional<std::uint16_t> broken_date_start() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
        return entry->broken_date_start.get();
    }

    std::optional<std::uint16_t> broken_date_end() const {
        auto* entry = reinterpret_cast<const md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
        return entry->broken_date_end.get();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class md_instrument_definition_repo_broken_dates_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    md_instrument_definition_repo_broken_dates_groups_reader(const std::byte* data, const std::byte* end)
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

    md_instrument_definition_repo_broken_dates_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        md_instrument_definition_repo_broken_dates_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline md_instrument_definition_repo_events_groups_reader read_events(const md_instrument_definition_repo& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline md_instrument_definition_repo_feed_types_groups_reader read_feed_types(const std::byte* pos, const md_instrument_definition_repo& msg) {
    return { pos, msg.tail_end() };
}

inline md_instrument_definition_repo_inst_attrib_groups_reader read_inst_attrib(const std::byte* pos, const md_instrument_definition_repo& msg) {
    return { pos, msg.tail_end() };
}

inline md_instrument_definition_repo_lot_type_rules_groups_reader read_lot_type_rules(const std::byte* pos, const md_instrument_definition_repo& msg) {
    return { pos, msg.tail_end() };
}

inline md_instrument_definition_repo_repo_underlyings_groups_reader read_repo_underlyings(const std::byte* pos, const md_instrument_definition_repo& msg) {
    return { pos, msg.tail_end() };
}

inline md_instrument_definition_repo_repo_related_instruments_groups_reader read_repo_related_instruments(const std::byte* pos, const md_instrument_definition_repo& msg) {
    return { pos, msg.tail_end() };
}

inline md_instrument_definition_repo_broken_dates_groups_reader read_broken_dates(const std::byte* pos, const md_instrument_definition_repo& msg) {
    return { pos, msg.tail_end() };
}

}
