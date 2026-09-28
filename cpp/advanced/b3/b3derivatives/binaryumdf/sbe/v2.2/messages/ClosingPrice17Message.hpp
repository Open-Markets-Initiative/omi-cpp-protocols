#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/Offset10Padding2.hpp"
#include "../types/MdCorporatePrice.hpp"
#include "../types/LastTradeDate.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_2;

#pragma pack(push, 1)

// Closing Price 17 Message
struct closing_price_17_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::open_close_settl_flag open_close_settl_flag;
        sbe_binaryumdf::offset_10_padding_2 offset_10_padding_2;
        sbe_binaryumdf::md_corporate_price md_corporate_price;
        sbe_binaryumdf::last_trade_date last_trade_date;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static closing_price_17_message* parse(std::byte* buffer) {
        return reinterpret_cast<closing_price_17_message*>(buffer);
    }

    // parse method const
    static const closing_price_17_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const closing_price_17_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(closing_price_17_message::fields_type, security_id) == 0, "unexpected offset of closing_price_17_message::fields_type::security_id");
static_assert(offsetof(closing_price_17_message::fields_type, match_event_indicator) == 8, "unexpected offset of closing_price_17_message::fields_type::match_event_indicator");
static_assert(offsetof(closing_price_17_message::fields_type, open_close_settl_flag) == 9, "unexpected offset of closing_price_17_message::fields_type::open_close_settl_flag");
static_assert(offsetof(closing_price_17_message::fields_type, offset_10_padding_2) == 10, "unexpected offset of closing_price_17_message::fields_type::offset_10_padding_2");
static_assert(offsetof(closing_price_17_message::fields_type, md_corporate_price) == 12, "unexpected offset of closing_price_17_message::fields_type::md_corporate_price");
static_assert(offsetof(closing_price_17_message::fields_type, last_trade_date) == 20, "unexpected offset of closing_price_17_message::fields_type::last_trade_date");
static_assert(offsetof(closing_price_17_message::fields_type, trade_date) == 22, "unexpected offset of closing_price_17_message::fields_type::trade_date");
static_assert(offsetof(closing_price_17_message::fields_type, md_entry_timestamp) == 24, "unexpected offset of closing_price_17_message::fields_type::md_entry_timestamp");
static_assert(offsetof(closing_price_17_message::fields_type, rpt_seq) == 32, "unexpected offset of closing_price_17_message::fields_type::rpt_seq");
static_assert(sizeof(closing_price_17_message::fields_type) == 36, "unexpected sizeof closing_price_17_message::fields_type");
static_assert(sizeof(closing_price_17_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 36, "unexpected sizeof closing_price_17_message");

#pragma pack(pop)
}
