#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/Offset11Padding1.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/NetChgPrevDay.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"
#include "../types/Padding2.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_7;

#pragma pack(push, 1)

// Opening Price 15 Message
struct opening_price_15_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::md_update_action md_update_action;
        sbe_binaryumdf::open_close_settl_flag open_close_settl_flag;
        sbe_binaryumdf::offset_11_padding_1 offset_11_padding_1;
        sbe_binaryumdf::md_future_price md_future_price;
        sbe_binaryumdf::net_chg_prev_day net_chg_prev_day;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
        sbe_binaryumdf::padding_2 padding_2;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static opening_price_15_message* parse(std::byte* buffer) {
        return reinterpret_cast<opening_price_15_message*>(buffer);
    }

    // parse method const
    static const opening_price_15_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const opening_price_15_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(opening_price_15_message::fields_type, security_id) == 0, "unexpected offset of opening_price_15_message::fields_type::security_id");
static_assert(offsetof(opening_price_15_message::fields_type, match_event_indicator) == 8, "unexpected offset of opening_price_15_message::fields_type::match_event_indicator");
static_assert(offsetof(opening_price_15_message::fields_type, md_update_action) == 9, "unexpected offset of opening_price_15_message::fields_type::md_update_action");
static_assert(offsetof(opening_price_15_message::fields_type, open_close_settl_flag) == 10, "unexpected offset of opening_price_15_message::fields_type::open_close_settl_flag");
static_assert(offsetof(opening_price_15_message::fields_type, offset_11_padding_1) == 11, "unexpected offset of opening_price_15_message::fields_type::offset_11_padding_1");
static_assert(offsetof(opening_price_15_message::fields_type, md_future_price) == 12, "unexpected offset of opening_price_15_message::fields_type::md_future_price");
static_assert(offsetof(opening_price_15_message::fields_type, net_chg_prev_day) == 20, "unexpected offset of opening_price_15_message::fields_type::net_chg_prev_day");
static_assert(offsetof(opening_price_15_message::fields_type, trade_date) == 28, "unexpected offset of opening_price_15_message::fields_type::trade_date");
static_assert(offsetof(opening_price_15_message::fields_type, md_entry_timestamp) == 30, "unexpected offset of opening_price_15_message::fields_type::md_entry_timestamp");
static_assert(offsetof(opening_price_15_message::fields_type, rpt_seq) == 38, "unexpected offset of opening_price_15_message::fields_type::rpt_seq");
static_assert(offsetof(opening_price_15_message::fields_type, padding_2) == 42, "unexpected offset of opening_price_15_message::fields_type::padding_2");
static_assert(sizeof(opening_price_15_message::fields_type) == 44, "unexpected sizeof opening_price_15_message::fields_type");
static_assert(sizeof(opening_price_15_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 44, "unexpected sizeof opening_price_15_message");

#pragma pack(pop)
}
