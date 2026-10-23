#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Padding2.hpp"
#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevel.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeBook.hpp"
#include "../types/Padding1.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/OrderId.hpp"
#include "../types/MdOrderPriorityOptional.hpp"
#include "../types/MdDisplayQtyOptional.hpp"
#include "../types/ReferenceId.hpp"
#include "../types/OrderUpdateAction.hpp"
#include "../structs/GroupSize8Byte.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry {
    sbe_mdp3::md_entry_px_optional_ex md_entry_px_optional_ex;
    sbe_mdp3::md_entry_size_optional md_entry_size_optional;
    sbe_mdp3::security_id security_id;
    sbe_mdp3::rpt_seq rpt_seq;
    sbe_mdp3::number_of_orders_optional number_of_orders_optional;
    sbe_mdp3::md_price_level md_price_level;
    sbe_mdp3::md_update_action md_update_action;
    sbe_mdp3::md_entry_type_book md_entry_type_book;
    sbe_mdp3::padding_1 padding_1;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry {
    sbe_mdp3::order_id order_id;
    sbe_mdp3::md_order_priority_optional md_order_priority_optional;
    sbe_mdp3::md_display_qty_optional md_display_qty_optional;
    sbe_mdp3::reference_id reference_id;
    sbe_mdp3::order_update_action order_update_action;
    sbe_mdp3::padding_2 padding_2;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Incremental Refresh Book Long Qty
struct md_incremental_refresh_book_long_qty {

    struct fields_type {
        sbe_mdp3::transact_time transact_time;
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::padding_2 padding_2;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::md_incremental_refresh_book_long_qty, schema_id::enum_type::mktdata, version(13)};

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
    sbe_group_iterator<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_groups_entry, group_size> incremental_refresh_book_long_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<md_incremental_refresh_book_long_qty_incremental_refresh_book_long_order_id_groups_entry, group_size_8_byte> incremental_refresh_book_long_order_id_groups(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static md_incremental_refresh_book_long_qty* parse(std::byte* buffer) {
        return reinterpret_cast<md_incremental_refresh_book_long_qty*>(buffer);
    }

    // parse method const
    static const md_incremental_refresh_book_long_qty* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_incremental_refresh_book_long_qty*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_incremental_refresh_book_long_qty::fields_type, transact_time) == 0, "unexpected offset of md_incremental_refresh_book_long_qty::fields_type::transact_time");
static_assert(offsetof(md_incremental_refresh_book_long_qty::fields_type, match_event_indicator) == 8, "unexpected offset of md_incremental_refresh_book_long_qty::fields_type::match_event_indicator");
static_assert(offsetof(md_incremental_refresh_book_long_qty::fields_type, padding_2) == 9, "unexpected offset of md_incremental_refresh_book_long_qty::fields_type::padding_2");
static_assert(sizeof(md_incremental_refresh_book_long_qty::fields_type) == 11, "unexpected sizeof md_incremental_refresh_book_long_qty::fields_type");

#pragma pack(pop)
}

#include "details/MdIncrementalRefreshBookLongQtyWriter.hpp"
#include "details/MdIncrementalRefreshBookLongQtyReader.hpp"
