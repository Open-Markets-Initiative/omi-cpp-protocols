#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/Offset11Padding5.hpp"
#include "../types/TransactTime.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

#pragma pack(push, 1)

// Mass Delete Orders Mb O 52 Message
struct mass_delete_orders_mb_o_52_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::md_update_action md_update_action;
        sbe_binaryumdf::md_entry_type md_entry_type;
        sbe_binaryumdf::offset_11_padding_5 offset_11_padding_5;
        sbe_binaryumdf::transact_time transact_time;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static mass_delete_orders_mb_o_52_message* parse(std::byte* buffer) {
        return reinterpret_cast<mass_delete_orders_mb_o_52_message*>(buffer);
    }

    // parse method const
    static const mass_delete_orders_mb_o_52_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const mass_delete_orders_mb_o_52_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(mass_delete_orders_mb_o_52_message::fields_type, security_id) == 0, "unexpected offset of mass_delete_orders_mb_o_52_message::fields_type::security_id");
static_assert(offsetof(mass_delete_orders_mb_o_52_message::fields_type, match_event_indicator) == 8, "unexpected offset of mass_delete_orders_mb_o_52_message::fields_type::match_event_indicator");
static_assert(offsetof(mass_delete_orders_mb_o_52_message::fields_type, md_update_action) == 9, "unexpected offset of mass_delete_orders_mb_o_52_message::fields_type::md_update_action");
static_assert(offsetof(mass_delete_orders_mb_o_52_message::fields_type, md_entry_type) == 10, "unexpected offset of mass_delete_orders_mb_o_52_message::fields_type::md_entry_type");
static_assert(offsetof(mass_delete_orders_mb_o_52_message::fields_type, offset_11_padding_5) == 11, "unexpected offset of mass_delete_orders_mb_o_52_message::fields_type::offset_11_padding_5");
static_assert(offsetof(mass_delete_orders_mb_o_52_message::fields_type, transact_time) == 16, "unexpected offset of mass_delete_orders_mb_o_52_message::fields_type::transact_time");
static_assert(offsetof(mass_delete_orders_mb_o_52_message::fields_type, rpt_seq) == 24, "unexpected offset of mass_delete_orders_mb_o_52_message::fields_type::rpt_seq");
static_assert(sizeof(mass_delete_orders_mb_o_52_message::fields_type) == 28, "unexpected sizeof mass_delete_orders_mb_o_52_message::fields_type");
static_assert(sizeof(mass_delete_orders_mb_o_52_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 28, "unexpected sizeof mass_delete_orders_mb_o_52_message");

#pragma pack(pop)
}
