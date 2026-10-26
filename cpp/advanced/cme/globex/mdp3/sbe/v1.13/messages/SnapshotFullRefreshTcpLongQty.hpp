#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/SecurityId.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeOptional.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevelUnsignedOptional.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/MdEntryType.hpp"
#include "../structs/GroupSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct snapshot_full_refresh_tcp_long_qty_snapshotfull_refresh_tcp_long_groups_entry {
    sbe_mdp3::md_entry_px_optional_ex md_entry_px_optional_ex;
    sbe_mdp3::md_entry_size_optional md_entry_size_optional;
    sbe_mdp3::number_of_orders_optional number_of_orders_optional;
    sbe_mdp3::md_price_level_unsigned_optional md_price_level_unsigned_optional;
    sbe_mdp3::open_close_settl_flag open_close_settl_flag;
    sbe_mdp3::md_entry_type md_entry_type;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Snapshot Full Refresh Tcp Long Qty
struct snapshot_full_refresh_tcp_long_qty {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::security_id security_id;
        sbe_mdp3::high_limit_price high_limit_price;
        sbe_mdp3::low_limit_price low_limit_price;
        sbe_mdp3::max_price_variation max_price_variation;
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
    sbe_group_iterator<snapshot_full_refresh_tcp_long_qty_snapshotfull_refresh_tcp_long_groups_entry, group_size> snapshotfull_refresh_tcp_long_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static snapshot_full_refresh_tcp_long_qty* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_full_refresh_tcp_long_qty*>(buffer);
    }

    // parse method const
    static const snapshot_full_refresh_tcp_long_qty* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_full_refresh_tcp_long_qty*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_full_refresh_tcp_long_qty::fields_type, transact_time) == 0, "unexpected offset of snapshot_full_refresh_tcp_long_qty::fields_type::transact_time");
static_assert(offsetof(snapshot_full_refresh_tcp_long_qty::fields_type, match_event_indicator) == 8, "unexpected offset of snapshot_full_refresh_tcp_long_qty::fields_type::match_event_indicator");
static_assert(offsetof(snapshot_full_refresh_tcp_long_qty::fields_type, security_id) == 9, "unexpected offset of snapshot_full_refresh_tcp_long_qty::fields_type::security_id");
static_assert(offsetof(snapshot_full_refresh_tcp_long_qty::fields_type, high_limit_price) == 13, "unexpected offset of snapshot_full_refresh_tcp_long_qty::fields_type::high_limit_price");
static_assert(offsetof(snapshot_full_refresh_tcp_long_qty::fields_type, low_limit_price) == 21, "unexpected offset of snapshot_full_refresh_tcp_long_qty::fields_type::low_limit_price");
static_assert(offsetof(snapshot_full_refresh_tcp_long_qty::fields_type, max_price_variation) == 29, "unexpected offset of snapshot_full_refresh_tcp_long_qty::fields_type::max_price_variation");
static_assert(sizeof(snapshot_full_refresh_tcp_long_qty::fields_type) == 37, "unexpected sizeof snapshot_full_refresh_tcp_long_qty::fields_type");

#pragma pack(pop)
}

#include "details/SnapshotFullRefreshTcpLongQtyWriter.hpp"
#include "details/SnapshotFullRefreshTcpLongQtyReader.hpp"
