#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderId.hpp"
#include "../types/MdOrderPriority.hpp"
#include "../types/MdEntryPxEx.hpp"
#include "../types/MdDisplayQty.hpp"
#include "../types/MdEntryTypeBook.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct snapshot_refresh_top_orders_groups_entry {
    sbe_mdp3::order_id order_id;
    sbe_mdp3::md_order_priority md_order_priority;
    sbe_mdp3::md_entry_px_ex md_entry_px_ex;
    sbe_mdp3::md_display_qty md_display_qty;
    sbe_mdp3::md_entry_type_book md_entry_type_book;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Snapshot Refresh Top Orders
struct snapshot_refresh_top_orders {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::security_id security_id;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::snapshot_refresh_top_orders, schema_id::enum_type::mktdata, version(13)};

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
    sbe_group_iterator<snapshot_refresh_top_orders_groups_entry, group_size> snapshot_refresh_top_orders_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static snapshot_refresh_top_orders* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_refresh_top_orders*>(buffer);
    }

    // parse method const
    static const snapshot_refresh_top_orders* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_refresh_top_orders*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_refresh_top_orders::fields_type, transact_time) == 0, "unexpected offset of snapshot_refresh_top_orders::fields_type::transact_time");
static_assert(offsetof(snapshot_refresh_top_orders::fields_type, match_event_indicator) == 8, "unexpected offset of snapshot_refresh_top_orders::fields_type::match_event_indicator");
static_assert(offsetof(snapshot_refresh_top_orders::fields_type, security_id) == 9, "unexpected offset of snapshot_refresh_top_orders::fields_type::security_id");
static_assert(sizeof(snapshot_refresh_top_orders::fields_type) == 13, "unexpected sizeof snapshot_refresh_top_orders::fields_type");

#pragma pack(pop)
}

#include "details/SnapshotRefreshTopOrdersWriter.hpp"
#include "details/SnapshotRefreshTopOrdersReader.hpp"
