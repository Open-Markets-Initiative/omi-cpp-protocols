#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v5 {

namespace sbe_mdp3 = ::cme::mdp3::v5;

#pragma pack(push, 1)
struct md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry {
    sbe_mdp3::high_limit_price high_limit_price;
    sbe_mdp3::low_limit_price low_limit_price;
    sbe_mdp3::max_price_variation max_price_variation;
    sbe_mdp3::security_id security_id;
    sbe_mdp3::rpt_seq rpt_seq;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Incremental Refresh Limits Banding
struct md_incremental_refresh_limits_banding {

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
    sbe_group_iterator<md_incremental_refresh_limits_banding_incremental_refresh_limits_banding_groups_entry, group_size> incremental_refresh_limits_banding_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static md_incremental_refresh_limits_banding* parse(std::byte* buffer) {
        return reinterpret_cast<md_incremental_refresh_limits_banding*>(buffer);
    }

    // parse method const
    static const md_incremental_refresh_limits_banding* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_incremental_refresh_limits_banding*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_incremental_refresh_limits_banding::fields_type, transact_time) == 0, "unexpected offset of md_incremental_refresh_limits_banding::fields_type::transact_time");
static_assert(offsetof(md_incremental_refresh_limits_banding::fields_type, match_event_indicator) == 8, "unexpected offset of md_incremental_refresh_limits_banding::fields_type::match_event_indicator");
static_assert(offsetof(md_incremental_refresh_limits_banding::fields_type, padding_2) == 9, "unexpected offset of md_incremental_refresh_limits_banding::fields_type::padding_2");
static_assert(sizeof(md_incremental_refresh_limits_banding::fields_type) == 11, "unexpected sizeof md_incremental_refresh_limits_banding::fields_type");

#pragma pack(pop)
}

#include "details/MdIncrementalRefreshLimitsBandingWriter.hpp"
#include "details/MdIncrementalRefreshLimitsBandingReader.hpp"
