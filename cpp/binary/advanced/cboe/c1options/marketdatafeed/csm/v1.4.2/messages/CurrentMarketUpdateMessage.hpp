#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/ClassKey.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/PriceType.hpp"
#include "../types/NoEntries.hpp"
#include "../types/MdEntryType.hpp"
#include "../structs/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdVolumeType.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)
struct current_market_update_message_md_entry_entry {
    csm_marketdatafeed::md_entry_type md_entry_type;
    csm_marketdatafeed::md_entry_px md_entry_px;
    csm_marketdatafeed::md_entry_size md_entry_size;
    csm_marketdatafeed::md_volume_type md_volume_type;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Current Market Update Message
struct current_market_update_message {

    struct fields_type {
        csm_marketdatafeed::class_key class_key;
        csm_marketdatafeed::security_id security_id;
        csm_marketdatafeed::security_trading_status security_trading_status;
        csm_marketdatafeed::price_type price_type;
        csm_marketdatafeed::no_entries no_entries;
    };

    csm_marketdatafeed::message_header header = {{}, template_id::enum_type::current_market_update_message, {}, {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(csm_marketdatafeed::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const { return tail + tail_capacity; }

    // sequential access to variable-length regions
    external_count_iterator<current_market_update_message_md_entry_entry> md_entry() const {
        return { tail_begin(), fields.no_entries.get().value(), tail_end() };
    }


    // parse method
    static current_market_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<current_market_update_message*>(buffer);
    }

    // parse method const
    static const current_market_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const current_market_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(current_market_update_message::fields_type, class_key) == 0, "unexpected offset of current_market_update_message::fields_type::class_key");
static_assert(offsetof(current_market_update_message::fields_type, security_id) == 4, "unexpected offset of current_market_update_message::fields_type::security_id");
static_assert(offsetof(current_market_update_message::fields_type, security_trading_status) == 8, "unexpected offset of current_market_update_message::fields_type::security_trading_status");
static_assert(offsetof(current_market_update_message::fields_type, price_type) == 9, "unexpected offset of current_market_update_message::fields_type::price_type");
static_assert(offsetof(current_market_update_message::fields_type, no_entries) == 10, "unexpected offset of current_market_update_message::fields_type::no_entries");
static_assert(sizeof(current_market_update_message::fields_type) == 11, "unexpected sizeof current_market_update_message::fields_type");

#pragma pack(pop)
}
