#pragma once

#include "../SecurityDefinitionMessage.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

class security_definition_message_group_writer;
class security_definition_message_underlyings_groups_builder;
class security_definition_message_after_underlyings;
class security_definition_message_legs_groups_builder;
class security_definition_message_after_legs;
class security_definition_message_instr_attribs_groups_builder;
class security_definition_message_after_instr_attribs;

class security_definition_message_underlyings_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_binaryumdf::group_size_encoding* header_;
    uint16_t count_ = 0;

public:
    security_definition_message_underlyings_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_binaryumdf::group_size_encoding) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_binaryumdf::group_size_encoding*>(pos_);
        header_->block_length.set(sizeof(security_definition_message_underlyings_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_binaryumdf::group_size_encoding);
    }

    security_definition_message_underlyings_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_binaryumdf::group_size_encoding* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    security_definition_message_underlyings_groups_builder& underlying_security_id(std::uint64_t v) {
        if (pos_ + sizeof(security_definition_message_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_underlyings_groups_entry*>(pos_);
        entry->underlying_security_id.set(v);
        return *this;
    }

    security_definition_message_underlyings_groups_builder& underlying_symbol(std::string_view v) {
        if (pos_ + sizeof(security_definition_message_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_underlyings_groups_entry*>(pos_);
        entry->underlying_symbol.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    security_definition_message_after_underlyings end_underlyings();
};

class security_definition_message_legs_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_binaryumdf::group_size_encoding* header_;
    uint16_t count_ = 0;

public:
    security_definition_message_legs_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_binaryumdf::group_size_encoding) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_binaryumdf::group_size_encoding*>(pos_);
        header_->block_length.set(sizeof(security_definition_message_legs_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_binaryumdf::group_size_encoding);
    }

    security_definition_message_legs_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_binaryumdf::group_size_encoding* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    security_definition_message_legs_groups_builder& leg_security_id(std::uint64_t v) {
        if (pos_ + sizeof(security_definition_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_legs_groups_entry*>(pos_);
        entry->leg_security_id.set(v);
        return *this;
    }

    security_definition_message_legs_groups_builder& leg_ratio_qty(typename sbe_binaryumdf::leg_ratio_qty::result_type v) {
        if (pos_ + sizeof(security_definition_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_legs_groups_entry*>(pos_);
        entry->leg_ratio_qty.set(v);
        return *this;
    }

    security_definition_message_legs_groups_builder& leg_security_type(sbe_binaryumdf::leg_security_type::enum_type v) {
        if (pos_ + sizeof(security_definition_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_legs_groups_entry*>(pos_);
        entry->leg_security_type.set(v);
        return *this;
    }

    security_definition_message_legs_groups_builder& leg_side(sbe_binaryumdf::leg_side::enum_type v) {
        if (pos_ + sizeof(security_definition_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_legs_groups_entry*>(pos_);
        entry->leg_side.set(v);
        return *this;
    }

    security_definition_message_legs_groups_builder& leg_symbol(std::string_view v) {
        if (pos_ + sizeof(security_definition_message_legs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_legs_groups_entry*>(pos_);
        entry->leg_symbol.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    security_definition_message_after_legs end_legs();
};

class security_definition_message_instr_attribs_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_binaryumdf::group_size_encoding* header_;
    uint16_t count_ = 0;

public:
    security_definition_message_instr_attribs_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_binaryumdf::group_size_encoding) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_binaryumdf::group_size_encoding*>(pos_);
        header_->block_length.set(sizeof(security_definition_message_instr_attribs_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_binaryumdf::group_size_encoding);
    }

    security_definition_message_instr_attribs_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_binaryumdf::group_size_encoding* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    security_definition_message_instr_attribs_groups_builder& instr_attrib_type(sbe_binaryumdf::instr_attrib_type::enum_type v) {
        if (pos_ + sizeof(security_definition_message_instr_attribs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_instr_attribs_groups_entry*>(pos_);
        entry->instr_attrib_type.set(v);
        return *this;
    }

    security_definition_message_instr_attribs_groups_builder& instr_attrib_value(sbe_binaryumdf::instr_attrib_value::enum_type v) {
        if (pos_ + sizeof(security_definition_message_instr_attribs_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<security_definition_message_instr_attribs_groups_entry*>(pos_);
        entry->instr_attrib_value.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    security_definition_message_after_instr_attribs end_instr_attribs();
};

class security_definition_message_after_underlyings {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_underlyings(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_legs_groups_builder start_legs() {
        return { msg_start_, pos_, end_ };
    }
};

class security_definition_message_after_legs {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_legs(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_instr_attribs_groups_builder start_instr_attribs() {
        return { msg_start_, pos_, end_ };
    }
};

class security_definition_message_after_instr_attribs {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_after_instr_attribs(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    std::span<std::byte> security_desc_and_finish(std::string_view v) {
        if (pos_ + sizeof(uint32_t) + v.size() > end_) throw std::runtime_error("buffer overrun writing var-data");
        *reinterpret_cast<uint32_t*>(pos_) = static_cast<uint32_t>(v.size());
        std::memcpy(pos_ + sizeof(uint32_t), v.data(), v.size());
        auto* final_pos = pos_ + sizeof(uint32_t) + v.size();
        reinterpret_cast<sbe_binaryumdf::framing_header*>(msg_start_)->message_length.set(static_cast<uint16_t>(final_pos - msg_start_));
        return { msg_start_, static_cast<size_t>(final_pos - msg_start_) };
    }
};

class security_definition_message_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    security_definition_message_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    security_definition_message_underlyings_groups_builder start_underlyings() {
        return { msg_start_, pos_, end_ };
    }
};

inline security_definition_message_after_underlyings security_definition_message_underlyings_groups_builder::end_underlyings() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline security_definition_message_after_legs security_definition_message_legs_groups_builder::end_legs() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline security_definition_message_after_instr_attribs security_definition_message_instr_attribs_groups_builder::end_instr_attribs() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}



inline security_definition_message_group_writer start_group_write(security_definition_message& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + security_definition_message::tail_capacity };
}
}
