#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/PriceType.hpp"
#include "../types/TradeVolume.hpp"
#include "../types/OpenInterest.hpp"
#include "../structs/NetChgPrevDay.hpp"
#include "../structs/UnderlyingPx.hpp"
#include "../types/NoEntries.hpp"
#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)
struct summary_message_summary_md_entry_entry {
    csm_marketdatafeed::md_entry_type md_entry_type;
    csm_marketdatafeed::md_entry_px md_entry_px;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Summary Message
struct summary_message {

    struct fields_type {
        csm_marketdatafeed::class_key class_key;
        csm_marketdatafeed::security_id security_id;
        csm_marketdatafeed::price_type price_type;
        csm_marketdatafeed::trade_volume trade_volume;
        csm_marketdatafeed::open_interest open_interest;
        csm_marketdatafeed::net_chg_prev_day net_chg_prev_day;
        csm_marketdatafeed::underlying_px underlying_px;
        csm_marketdatafeed::no_entries no_entries;
    };

    csm_marketdatafeed::message_header header = {{}, template_id::enum_type::summary_message, {}, {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(csm_marketdatafeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const { return tail + tail_capacity; }

    // sequential access to variable-length regions
    external_count_iterator<summary_message_summary_md_entry_entry> summary_md_entry() const {
        return { tail_begin(), fields.no_entries.get().value(), tail_end() };
    }


    // parse method
    static summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<summary_message*>(buffer);
    }

    // parse method const
    static const summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(summary_message::fields_type, class_key) == 0, "unexpected offset of summary_message::fields_type::class_key");
static_assert(offsetof(summary_message::fields_type, security_id) == 4, "unexpected offset of summary_message::fields_type::security_id");
static_assert(offsetof(summary_message::fields_type, price_type) == 8, "unexpected offset of summary_message::fields_type::price_type");
static_assert(offsetof(summary_message::fields_type, trade_volume) == 9, "unexpected offset of summary_message::fields_type::trade_volume");
static_assert(offsetof(summary_message::fields_type, open_interest) == 13, "unexpected offset of summary_message::fields_type::open_interest");
static_assert(offsetof(summary_message::fields_type, net_chg_prev_day) == 17, "unexpected offset of summary_message::fields_type::net_chg_prev_day");
static_assert(offsetof(summary_message::fields_type, underlying_px) == 22, "unexpected offset of summary_message::fields_type::underlying_px");
static_assert(offsetof(summary_message::fields_type, no_entries) == 27, "unexpected offset of summary_message::fields_type::no_entries");
static_assert(sizeof(summary_message::fields_type) == 28, "unexpected sizeof summary_message::fields_type");

#pragma pack(pop)
}
