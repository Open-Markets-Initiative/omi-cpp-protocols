#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/Padding7.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct md_incremental_refresh_volume_long_qty_incremental_refresh_volume_long_groups_entry {
    sbe_mdp3::md_entry_size md_entry_size;
    sbe_mdp3::security_id security_id;
    sbe_mdp3::rpt_seq rpt_seq;
    sbe_mdp3::md_update_action md_update_action;
    sbe_mdp3::padding_7 padding_7;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Incremental Refresh Volume Long Qty
struct md_incremental_refresh_volume_long_qty {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::padding_2 padding_2;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<md_incremental_refresh_volume_long_qty_incremental_refresh_volume_long_groups_entry, group_size> incremental_refresh_volume_long_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static md_incremental_refresh_volume_long_qty* parse(std::byte* buffer) {
        return reinterpret_cast<md_incremental_refresh_volume_long_qty*>(buffer);
    }

    // parse method const
    static const md_incremental_refresh_volume_long_qty* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_incremental_refresh_volume_long_qty*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_incremental_refresh_volume_long_qty::fields_type, transact_time) == 0, "unexpected offset of md_incremental_refresh_volume_long_qty::fields_type::transact_time");
static_assert(offsetof(md_incremental_refresh_volume_long_qty::fields_type, match_event_indicator) == 8, "unexpected offset of md_incremental_refresh_volume_long_qty::fields_type::match_event_indicator");
static_assert(offsetof(md_incremental_refresh_volume_long_qty::fields_type, padding_2) == 9, "unexpected offset of md_incremental_refresh_volume_long_qty::fields_type::padding_2");
static_assert(sizeof(md_incremental_refresh_volume_long_qty::fields_type) == 11, "unexpected sizeof md_incremental_refresh_volume_long_qty::fields_type");

#pragma pack(pop)
}

#include "details/MdIncrementalRefreshVolumeLongQtyWriter.hpp"
#include "details/MdIncrementalRefreshVolumeLongQtyReader.hpp"
