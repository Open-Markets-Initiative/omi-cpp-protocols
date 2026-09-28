#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MdCorporateOffsetPriceOptional.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/Offset16Padding4.hpp"
#include "../types/EnteringFirm.hpp"
#include "../types/MdInsertTimestamp.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

#pragma pack(push, 1)
struct snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry {
    sbe_binaryumdf::md_corporate_offset_price_optional md_corporate_offset_price_optional;
    sbe_binaryumdf::md_entry_size_quantity md_entry_size_quantity;
    sbe_binaryumdf::offset_16_padding_4 offset_16_padding_4;
    sbe_binaryumdf::entering_firm entering_firm;
    sbe_binaryumdf::md_insert_timestamp md_insert_timestamp;
    sbe_binaryumdf::secondary_order_id secondary_order_id;
    sbe_binaryumdf::md_entry_type md_entry_type;
    sbe_binaryumdf::match_event_indicator match_event_indicator;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Snapshot Full Refresh Orders Mb O 71 Message
struct snapshot_full_refresh_orders_mb_o_71_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_binaryumdf::framing_header) - sizeof(fields_type) - sizeof(sbe_binaryumdf::message_header);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return sz == sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_binaryumdf::framing_header) - sizeof(fields_type) - sizeof(sbe_binaryumdf::message_header));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups_entry, group_size_encoding> snapshot_full_refresh_orders_mb_o_71_message_no_m_d_entries_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static snapshot_full_refresh_orders_mb_o_71_message* parse(std::byte* buffer) {
        return reinterpret_cast<snapshot_full_refresh_orders_mb_o_71_message*>(buffer);
    }

    // parse method const
    static const snapshot_full_refresh_orders_mb_o_71_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const snapshot_full_refresh_orders_mb_o_71_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(snapshot_full_refresh_orders_mb_o_71_message::fields_type, security_id) == 0, "unexpected offset of snapshot_full_refresh_orders_mb_o_71_message::fields_type::security_id");
static_assert(sizeof(snapshot_full_refresh_orders_mb_o_71_message::fields_type) == 8, "unexpected sizeof snapshot_full_refresh_orders_mb_o_71_message::fields_type");

#pragma pack(pop)
}

#include "details/SnapshotFullRefreshOrdersMbO71MessageWriter.hpp"
#include "details/SnapshotFullRefreshOrdersMbO71MessageReader.hpp"
