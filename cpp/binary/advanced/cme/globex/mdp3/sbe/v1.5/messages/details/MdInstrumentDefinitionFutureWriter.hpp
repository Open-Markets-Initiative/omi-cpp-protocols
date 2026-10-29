#pragma once

#include "../MdInstrumentDefinitionFuture.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

class md_instrument_definition_future_group_writer;
class md_instrument_definition_future_events_groups_builder;
class md_instrument_definition_future_after_events;
class md_instrument_definition_future_feed_types_groups_builder;
class md_instrument_definition_future_after_feed_types;
class md_instrument_definition_future_inst_attrib_groups_builder;
class md_instrument_definition_future_after_inst_attrib;
class md_instrument_definition_future_lot_type_rules_groups_builder;

class md_instrument_definition_future_events_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_future_events_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_future_events_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_future_events_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_future_events_groups_builder& event_type(sbe_mdp3::event_type::enum_type v) {
        if (pos_ + sizeof(md_instrument_definition_future_events_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_future_events_groups_entry*>(pos_);
        entry->event_type.set(v);
        return *this;
    }

    md_instrument_definition_future_events_groups_builder& event_time(std::uint64_t v) {
        if (pos_ + sizeof(md_instrument_definition_future_events_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_future_events_groups_entry*>(pos_);
        entry->event_time.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_future_after_events end_events();
};

class md_instrument_definition_future_feed_types_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_future_feed_types_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_future_feed_types_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_future_feed_types_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_future_feed_types_groups_builder& md_feed_type(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_future_feed_types_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_future_feed_types_groups_entry*>(pos_);
        entry->md_feed_type.set(v);
        return *this;
    }

    md_instrument_definition_future_feed_types_groups_builder& market_depth(std::int8_t v) {
        if (pos_ + sizeof(md_instrument_definition_future_feed_types_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_future_feed_types_groups_entry*>(pos_);
        entry->market_depth.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_future_after_feed_types end_feed_types();
};

class md_instrument_definition_future_inst_attrib_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_future_inst_attrib_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_future_inst_attrib_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_future_inst_attrib_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_future_inst_attrib_groups_builder& inst_attrib_value(std::uint32_t v) {
        if (pos_ + sizeof(md_instrument_definition_future_inst_attrib_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_future_inst_attrib_groups_entry*>(pos_);
        entry->inst_attrib_value.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_future_after_inst_attrib end_inst_attrib();
};

class md_instrument_definition_future_lot_type_rules_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_future_lot_type_rules_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_future_lot_type_rules_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_future_lot_type_rules_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_future_lot_type_rules_groups_builder& lot_type(std::int8_t v) {
        if (pos_ + sizeof(md_instrument_definition_future_lot_type_rules_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_future_lot_type_rules_groups_entry*>(pos_);
        entry->lot_type.set(v);
        return *this;
    }

    md_instrument_definition_future_lot_type_rules_groups_builder& min_lot_size(typename sbe_mdp3::min_lot_size::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_future_lot_type_rules_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_future_lot_type_rules_groups_entry*>(pos_);
        entry->min_lot_size.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_lot_type_rules() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class md_instrument_definition_future_after_events {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_future_after_events(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_future_feed_types_groups_builder start_feed_types() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_future_after_feed_types {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_future_after_feed_types(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_future_inst_attrib_groups_builder start_inst_attrib() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_future_after_inst_attrib {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_future_after_inst_attrib(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_future_lot_type_rules_groups_builder start_lot_type_rules() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_future_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_future_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_future_events_groups_builder start_events() {
        return { msg_start_, pos_, end_ };
    }
};

inline md_instrument_definition_future_after_events md_instrument_definition_future_events_groups_builder::end_events() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline md_instrument_definition_future_after_feed_types md_instrument_definition_future_feed_types_groups_builder::end_feed_types() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline md_instrument_definition_future_after_inst_attrib md_instrument_definition_future_inst_attrib_groups_builder::end_inst_attrib() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}



inline md_instrument_definition_future_group_writer start_group_write(md_instrument_definition_future& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + md_instrument_definition_future::tail_capacity };
}
}
