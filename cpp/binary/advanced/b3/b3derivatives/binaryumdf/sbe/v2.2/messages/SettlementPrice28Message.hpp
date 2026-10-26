#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Offset9Padding1.hpp"
#include "../types/TradeDate.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/PriceType.hpp"
#include "../types/SettlPriceType.hpp"
#include "../types/RptSeq.hpp"
#include "../types/Padding1.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_2;

#pragma pack(push, 1)

// Settlement Price 28 Message
struct settlement_price_28_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::offset_9_padding_1 offset_9_padding_1;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::md_future_price md_future_price;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::open_close_settl_flag open_close_settl_flag;
        sbe_binaryumdf::price_type price_type;
        sbe_binaryumdf::settl_price_type settl_price_type;
        sbe_binaryumdf::rpt_seq rpt_seq;
        sbe_binaryumdf::padding_1 padding_1;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static settlement_price_28_message* parse(std::byte* buffer) {
        return reinterpret_cast<settlement_price_28_message*>(buffer);
    }

    // parse method const
    static const settlement_price_28_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const settlement_price_28_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(settlement_price_28_message::fields_type, security_id) == 0, "unexpected offset of settlement_price_28_message::fields_type::security_id");
static_assert(offsetof(settlement_price_28_message::fields_type, match_event_indicator) == 8, "unexpected offset of settlement_price_28_message::fields_type::match_event_indicator");
static_assert(offsetof(settlement_price_28_message::fields_type, offset_9_padding_1) == 9, "unexpected offset of settlement_price_28_message::fields_type::offset_9_padding_1");
static_assert(offsetof(settlement_price_28_message::fields_type, trade_date) == 10, "unexpected offset of settlement_price_28_message::fields_type::trade_date");
static_assert(offsetof(settlement_price_28_message::fields_type, md_future_price) == 12, "unexpected offset of settlement_price_28_message::fields_type::md_future_price");
static_assert(offsetof(settlement_price_28_message::fields_type, md_entry_timestamp) == 20, "unexpected offset of settlement_price_28_message::fields_type::md_entry_timestamp");
static_assert(offsetof(settlement_price_28_message::fields_type, open_close_settl_flag) == 28, "unexpected offset of settlement_price_28_message::fields_type::open_close_settl_flag");
static_assert(offsetof(settlement_price_28_message::fields_type, price_type) == 29, "unexpected offset of settlement_price_28_message::fields_type::price_type");
static_assert(offsetof(settlement_price_28_message::fields_type, settl_price_type) == 30, "unexpected offset of settlement_price_28_message::fields_type::settl_price_type");
static_assert(offsetof(settlement_price_28_message::fields_type, rpt_seq) == 31, "unexpected offset of settlement_price_28_message::fields_type::rpt_seq");
static_assert(offsetof(settlement_price_28_message::fields_type, padding_1) == 35, "unexpected offset of settlement_price_28_message::fields_type::padding_1");
static_assert(sizeof(settlement_price_28_message::fields_type) == 36, "unexpected sizeof settlement_price_28_message::fields_type");
static_assert(sizeof(settlement_price_28_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 36, "unexpected sizeof settlement_price_28_message");

#pragma pack(pop)
}
