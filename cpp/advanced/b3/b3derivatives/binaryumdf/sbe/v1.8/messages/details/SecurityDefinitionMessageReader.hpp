#pragma once

#include "SecurityDefinitionMessageWriter.hpp"
#include <optional>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

class security_definition_message_underlyings_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    security_definition_message_underlyings_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    std::uint64_t underlying_security_id() const {
        auto* entry = reinterpret_cast<const security_definition_message_underlyings_groups_entry*>(pos_);
        return entry->underlying_security_id.get().value();
    }

    std::string_view underlying_symbol() const {
        auto* entry = reinterpret_cast<const security_definition_message_underlyings_groups_entry*>(pos_);
        return entry->underlying_symbol.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class security_definition_message_underlyings_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    security_definition_message_underlyings_groups_reader(const std::byte* data, const std::byte* end)
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

    security_definition_message_underlyings_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        security_definition_message_underlyings_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class security_definition_message_legs_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    security_definition_message_legs_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    std::uint64_t leg_security_id() const {
        auto* entry = reinterpret_cast<const security_definition_message_legs_groups_entry*>(pos_);
        return entry->leg_security_id.get().value();
    }

    std::optional<std::int64_t> leg_ratio_qty() const {
        auto* entry = reinterpret_cast<const security_definition_message_legs_groups_entry*>(pos_);
        return entry->leg_ratio_qty.get();
    }

    sbe_binaryumdf::leg_security_type::enum_type leg_security_type() const {
        auto* entry = reinterpret_cast<const security_definition_message_legs_groups_entry*>(pos_);
        return entry->leg_security_type.get().value();
    }

    sbe_binaryumdf::leg_side::enum_type leg_side() const {
        auto* entry = reinterpret_cast<const security_definition_message_legs_groups_entry*>(pos_);
        return entry->leg_side.get().value();
    }

    std::string_view leg_symbol() const {
        auto* entry = reinterpret_cast<const security_definition_message_legs_groups_entry*>(pos_);
        return entry->leg_symbol.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class security_definition_message_legs_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    security_definition_message_legs_groups_reader(const std::byte* data, const std::byte* end)
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

    security_definition_message_legs_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        security_definition_message_legs_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};

class security_definition_message_instr_attribs_groups_entry_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;

public:
    security_definition_message_instr_attribs_groups_entry_reader(const std::byte* pos, const std::byte* end, uint16_t block_length)
        : pos_(pos), end_(end), block_length_(block_length) {
    }

    sbe_binaryumdf::instr_attrib_type::enum_type instr_attrib_type() const {
        auto* entry = reinterpret_cast<const security_definition_message_instr_attribs_groups_entry*>(pos_);
        return entry->instr_attrib_type.get().value();
    }

    sbe_binaryumdf::instr_attrib_value::enum_type instr_attrib_value() const {
        auto* entry = reinterpret_cast<const security_definition_message_instr_attribs_groups_entry*>(pos_);
        return entry->instr_attrib_value.get().value();
    }

    const std::byte* end_position() const { return pos_ + block_length_; }
};

class security_definition_message_instr_attribs_groups_reader {
    const std::byte* pos_;
    const std::byte* end_;
    uint16_t block_length_;
    uint16_t count_;
    uint16_t index_;

public:
    security_definition_message_instr_attribs_groups_reader(const std::byte* data, const std::byte* end)
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

    security_definition_message_instr_attribs_groups_entry_reader next() {
        if (!has_next()) throw std::runtime_error("no more entries in group");
        security_definition_message_instr_attribs_groups_entry_reader entry(pos_, end_, block_length_);
        pos_ = entry.end_position();
        ++index_;
        return entry;
    }

    void skip_remaining() {
        while (has_next()) { next(); }
    }

    const std::byte* end_position() const { return pos_; }
};


inline security_definition_message_underlyings_groups_reader read_underlyings(const security_definition_message& msg) {
    return { msg.tail_begin(), msg.tail_end() };
}

inline security_definition_message_legs_groups_reader read_legs(const std::byte* pos, const security_definition_message& msg) {
    return { pos, msg.tail_end() };
}

inline security_definition_message_instr_attribs_groups_reader read_instr_attribs(const std::byte* pos, const security_definition_message& msg) {
    return { pos, msg.tail_end() };
}

inline sbe_var_data read_security_desc(const std::byte* pos, const security_definition_message& msg) {
    return { pos, msg.tail_end() };
}

}
