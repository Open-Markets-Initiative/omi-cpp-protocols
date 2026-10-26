#pragma once

#include "../MdInstrumentDefinitionRepo.hpp"
#include <span>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

class md_instrument_definition_repo_group_writer;
class md_instrument_definition_repo_events_groups_builder;
class md_instrument_definition_repo_after_events;
class md_instrument_definition_repo_feed_types_groups_builder;
class md_instrument_definition_repo_after_feed_types;
class md_instrument_definition_repo_inst_attrib_groups_builder;
class md_instrument_definition_repo_after_inst_attrib;
class md_instrument_definition_repo_lot_type_rules_groups_builder;
class md_instrument_definition_repo_after_lot_type_rules;
class md_instrument_definition_repo_repo_underlyings_groups_builder;
class md_instrument_definition_repo_after_repo_underlyings;
class md_instrument_definition_repo_repo_related_instruments_groups_builder;
class md_instrument_definition_repo_after_repo_related_instruments;
class md_instrument_definition_repo_broken_dates_groups_builder;

class md_instrument_definition_repo_events_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_repo_events_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_repo_events_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_repo_events_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_repo_events_groups_builder& event_type(sbe_mdp3::event_type::enum_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_events_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_events_groups_entry*>(pos_);
        entry->event_type.set(v);
        return *this;
    }

    md_instrument_definition_repo_events_groups_builder& event_time(std::uint64_t v) {
        if (pos_ + sizeof(md_instrument_definition_repo_events_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_events_groups_entry*>(pos_);
        entry->event_time.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_repo_after_events end_events();
};

class md_instrument_definition_repo_feed_types_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_repo_feed_types_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_repo_feed_types_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_repo_feed_types_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_repo_feed_types_groups_builder& md_feed_type(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_repo_feed_types_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_feed_types_groups_entry*>(pos_);
        entry->md_feed_type.set(v);
        return *this;
    }

    md_instrument_definition_repo_feed_types_groups_builder& market_depth(std::int8_t v) {
        if (pos_ + sizeof(md_instrument_definition_repo_feed_types_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_feed_types_groups_entry*>(pos_);
        entry->market_depth.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_repo_after_feed_types end_feed_types();
};

class md_instrument_definition_repo_inst_attrib_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_repo_inst_attrib_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_repo_inst_attrib_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_repo_inst_attrib_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_repo_inst_attrib_groups_builder& inst_attrib_value(std::uint32_t v) {
        if (pos_ + sizeof(md_instrument_definition_repo_inst_attrib_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_inst_attrib_groups_entry*>(pos_);
        entry->inst_attrib_value.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_repo_after_inst_attrib end_inst_attrib();
};

class md_instrument_definition_repo_lot_type_rules_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_repo_lot_type_rules_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_repo_lot_type_rules_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_repo_lot_type_rules_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_repo_lot_type_rules_groups_builder& lot_type(std::int8_t v) {
        if (pos_ + sizeof(md_instrument_definition_repo_lot_type_rules_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_lot_type_rules_groups_entry*>(pos_);
        entry->lot_type.set(v);
        return *this;
    }

    md_instrument_definition_repo_lot_type_rules_groups_builder& min_lot_size_decimal_qty(typename sbe_mdp3::min_lot_size_decimal_qty::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_lot_type_rules_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_lot_type_rules_groups_entry*>(pos_);
        entry->min_lot_size_decimal_qty.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_repo_after_lot_type_rules end_lot_type_rules();
};

class md_instrument_definition_repo_repo_underlyings_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_repo_repo_underlyings_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_symbol(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_symbol.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_security_id_optional(typename sbe_mdp3::underlying_security_id_optional::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_security_id_optional.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_security_alt_id(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_security_alt_id.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_security_alt_id_source(sbe_mdp3::underlying_security_alt_id_source::enum_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_security_alt_id_source.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_financial_instrument_full_name(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_financial_instrument_full_name.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_security_type(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_security_type.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_country_of_issue(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_country_of_issue.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_issuer(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_issuer.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_max_life_time(typename sbe_mdp3::underlying_max_life_time::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_max_life_time.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_min_days_to_maturity(typename sbe_mdp3::underlying_min_days_to_maturity::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_min_days_to_maturity.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_instrument_guid_optional(typename sbe_mdp3::underlying_instrument_guid_optional::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_instrument_guid_optional.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_underlyings_groups_builder& underlying_maturity_date(typename sbe_mdp3::underlying_maturity_date::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_underlyings_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_underlyings_groups_entry*>(pos_);
        entry->underlying_maturity_date.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_repo_after_repo_underlyings end_repo_underlyings();
};

class md_instrument_definition_repo_repo_related_instruments_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_repo_repo_related_instruments_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_repo_repo_related_instruments_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_repo_repo_related_instruments_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_repo_repo_related_instruments_groups_builder& related_security_id(std::int32_t v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_related_instruments_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_related_instruments_groups_entry*>(pos_);
        entry->related_security_id.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_related_instruments_groups_builder& related_symbol(std::string_view v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_related_instruments_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_related_instruments_groups_entry*>(pos_);
        entry->related_symbol.set(v);
        return *this;
    }

    md_instrument_definition_repo_repo_related_instruments_groups_builder& related_instrument_guid(typename sbe_mdp3::related_instrument_guid::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_repo_related_instruments_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_repo_related_instruments_groups_entry*>(pos_);
        entry->related_instrument_guid.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    md_instrument_definition_repo_after_repo_related_instruments end_repo_related_instruments();
};

class md_instrument_definition_repo_broken_dates_groups_builder {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;
    sbe_mdp3::group_size* header_;
    uint16_t count_ = 0;

public:
    md_instrument_definition_repo_broken_dates_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {
        if (pos_ + sizeof(sbe_mdp3::group_size) > end_) throw std::runtime_error("buffer overrun writing group header");
        header_ = reinterpret_cast<sbe_mdp3::group_size*>(pos_);
        header_->block_length.set(sizeof(md_instrument_definition_repo_broken_dates_groups_entry));
        header_->num_in_group.set(0);
        pos_ += sizeof(sbe_mdp3::group_size);
    }

    md_instrument_definition_repo_broken_dates_groups_builder(std::byte* msg_start, std::byte* pos, std::byte* end, sbe_mdp3::group_size* header, uint16_t count)
        : msg_start_(msg_start), pos_(pos), end_(end), header_(header), count_(count) {}

    md_instrument_definition_repo_broken_dates_groups_builder& broken_date_guid(std::uint64_t v) {
        if (pos_ + sizeof(md_instrument_definition_repo_broken_dates_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
        entry->broken_date_guid.set(v);
        return *this;
    }

    md_instrument_definition_repo_broken_dates_groups_builder& broken_date_security_id(std::int32_t v) {
        if (pos_ + sizeof(md_instrument_definition_repo_broken_dates_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
        entry->broken_date_security_id.set(v);
        return *this;
    }

    md_instrument_definition_repo_broken_dates_groups_builder& broken_date_start(typename sbe_mdp3::broken_date_start::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_broken_dates_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
        entry->broken_date_start.set(v);
        return *this;
    }

    md_instrument_definition_repo_broken_dates_groups_builder& broken_date_end(typename sbe_mdp3::broken_date_end::result_type v) {
        if (pos_ + sizeof(md_instrument_definition_repo_broken_dates_groups_entry) > end_) throw std::runtime_error("buffer overrun writing group entry");
        auto* entry = reinterpret_cast<md_instrument_definition_repo_broken_dates_groups_entry*>(pos_);
        entry->broken_date_end.set(v);
        pos_ += header_->block_length.get().value();
        count_++;
        return *this;
    }

    std::span<std::byte> end_broken_dates() {
        header_->num_in_group.set(count_);
        reinterpret_cast<sbe_mdp3::message_header*>(msg_start_)->message_size.set(static_cast<uint16_t>(pos_ - msg_start_));
        return { msg_start_, static_cast<size_t>(pos_ - msg_start_) };
    }
};

class md_instrument_definition_repo_after_events {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_repo_after_events(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_repo_feed_types_groups_builder start_feed_types() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_repo_after_feed_types {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_repo_after_feed_types(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_repo_inst_attrib_groups_builder start_inst_attrib() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_repo_after_inst_attrib {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_repo_after_inst_attrib(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_repo_lot_type_rules_groups_builder start_lot_type_rules() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_repo_after_lot_type_rules {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_repo_after_lot_type_rules(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_repo_repo_underlyings_groups_builder start_repo_underlyings() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_repo_after_repo_underlyings {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_repo_after_repo_underlyings(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_repo_repo_related_instruments_groups_builder start_repo_related_instruments() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_repo_after_repo_related_instruments {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_repo_after_repo_related_instruments(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_repo_broken_dates_groups_builder start_broken_dates() {
        return { msg_start_, pos_, end_ };
    }
};

class md_instrument_definition_repo_group_writer {
    std::byte* msg_start_;
    std::byte* pos_;
    std::byte* end_;

public:
    md_instrument_definition_repo_group_writer(std::byte* msg_start, std::byte* pos, std::byte* end)
        : msg_start_(msg_start), pos_(pos), end_(end) {}

    md_instrument_definition_repo_events_groups_builder start_events() {
        return { msg_start_, pos_, end_ };
    }
};

inline md_instrument_definition_repo_after_events md_instrument_definition_repo_events_groups_builder::end_events() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline md_instrument_definition_repo_after_feed_types md_instrument_definition_repo_feed_types_groups_builder::end_feed_types() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline md_instrument_definition_repo_after_inst_attrib md_instrument_definition_repo_inst_attrib_groups_builder::end_inst_attrib() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline md_instrument_definition_repo_after_lot_type_rules md_instrument_definition_repo_lot_type_rules_groups_builder::end_lot_type_rules() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline md_instrument_definition_repo_after_repo_underlyings md_instrument_definition_repo_repo_underlyings_groups_builder::end_repo_underlyings() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}

inline md_instrument_definition_repo_after_repo_related_instruments md_instrument_definition_repo_repo_related_instruments_groups_builder::end_repo_related_instruments() {
    header_->num_in_group.set(count_);
    return { msg_start_, pos_, end_ };
}



inline md_instrument_definition_repo_group_writer start_group_write(md_instrument_definition_repo& msg) {
    return { reinterpret_cast<std::byte*>(&msg), msg.tail, msg.tail + md_instrument_definition_repo::tail_capacity };
}
}
