#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/SettlPriceType.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeDailyStatistics.hpp"
#include "../types/Padding7.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry {
    sbe_mdp3::md_entry_px_optional_ex md_entry_px_optional_ex;
    sbe_mdp3::md_entry_size_short_optional md_entry_size_short_optional;
    sbe_mdp3::security_id security_id;
    sbe_mdp3::rpt_seq rpt_seq;
    sbe_mdp3::trading_reference_date trading_reference_date;
    sbe_mdp3::settl_price_type settl_price_type;
    sbe_mdp3::md_update_action md_update_action;
    sbe_mdp3::md_entry_type_daily_statistics md_entry_type_daily_statistics;
    sbe_mdp3::padding_7 padding_7;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Incremental Refresh Daily Statistics
struct md_incremental_refresh_daily_statistics {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::padding_2 padding_2;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::md_incremental_refresh_daily_statistics, schema_id::enum_type::mktdata, version(13)};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type) + sizeof(sbe_mdp3::message_size)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<md_incremental_refresh_daily_statistics_incremental_refresh_daily_statistics_groups_entry, group_size> incremental_refresh_daily_statistics_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static md_incremental_refresh_daily_statistics* parse(std::byte* buffer) {
        return reinterpret_cast<md_incremental_refresh_daily_statistics*>(buffer);
    }

    // parse method const
    static const md_incremental_refresh_daily_statistics* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_incremental_refresh_daily_statistics*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_incremental_refresh_daily_statistics::fields_type, transact_time) == 0, "unexpected offset of md_incremental_refresh_daily_statistics::fields_type::transact_time");
static_assert(offsetof(md_incremental_refresh_daily_statistics::fields_type, match_event_indicator) == 8, "unexpected offset of md_incremental_refresh_daily_statistics::fields_type::match_event_indicator");
static_assert(offsetof(md_incremental_refresh_daily_statistics::fields_type, padding_2) == 9, "unexpected offset of md_incremental_refresh_daily_statistics::fields_type::padding_2");
static_assert(sizeof(md_incremental_refresh_daily_statistics::fields_type) == 11, "unexpected sizeof md_incremental_refresh_daily_statistics::fields_type");

#pragma pack(pop)
}

#include "details/MdIncrementalRefreshDailyStatisticsWriter.hpp"
#include "details/MdIncrementalRefreshDailyStatisticsReader.hpp"
