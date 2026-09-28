#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/TradeId.hpp"
#include "../types/MdEntryBuyer.hpp"
#include "../types/MdEntrySeller.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TrdSubType.hpp"
#include "../types/Offset43Padding1.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_9;

#pragma pack(push, 1)

// Trade 53 Message
struct trade_53_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::trading_session_id trading_session_id;
        sbe_binaryumdf::trade_condition trade_condition;
        sbe_binaryumdf::md_future_price md_future_price;
        sbe_binaryumdf::md_entry_size_quantity md_entry_size_quantity;
        sbe_binaryumdf::trade_id trade_id;
        sbe_binaryumdf::md_entry_buyer md_entry_buyer;
        sbe_binaryumdf::md_entry_seller md_entry_seller;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::trd_sub_type trd_sub_type;
        sbe_binaryumdf::offset_43_padding_1 offset_43_padding_1;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static trade_53_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_53_message*>(buffer);
    }

    // parse method const
    static const trade_53_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_53_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_53_message::fields_type, security_id) == 0, "unexpected offset of trade_53_message::fields_type::security_id");
static_assert(offsetof(trade_53_message::fields_type, match_event_indicator) == 8, "unexpected offset of trade_53_message::fields_type::match_event_indicator");
static_assert(offsetof(trade_53_message::fields_type, trading_session_id) == 9, "unexpected offset of trade_53_message::fields_type::trading_session_id");
static_assert(offsetof(trade_53_message::fields_type, trade_condition) == 10, "unexpected offset of trade_53_message::fields_type::trade_condition");
static_assert(offsetof(trade_53_message::fields_type, md_future_price) == 12, "unexpected offset of trade_53_message::fields_type::md_future_price");
static_assert(offsetof(trade_53_message::fields_type, md_entry_size_quantity) == 20, "unexpected offset of trade_53_message::fields_type::md_entry_size_quantity");
static_assert(offsetof(trade_53_message::fields_type, trade_id) == 28, "unexpected offset of trade_53_message::fields_type::trade_id");
static_assert(offsetof(trade_53_message::fields_type, md_entry_buyer) == 32, "unexpected offset of trade_53_message::fields_type::md_entry_buyer");
static_assert(offsetof(trade_53_message::fields_type, md_entry_seller) == 36, "unexpected offset of trade_53_message::fields_type::md_entry_seller");
static_assert(offsetof(trade_53_message::fields_type, trade_date) == 40, "unexpected offset of trade_53_message::fields_type::trade_date");
static_assert(offsetof(trade_53_message::fields_type, trd_sub_type) == 42, "unexpected offset of trade_53_message::fields_type::trd_sub_type");
static_assert(offsetof(trade_53_message::fields_type, offset_43_padding_1) == 43, "unexpected offset of trade_53_message::fields_type::offset_43_padding_1");
static_assert(offsetof(trade_53_message::fields_type, md_entry_timestamp) == 44, "unexpected offset of trade_53_message::fields_type::md_entry_timestamp");
static_assert(offsetof(trade_53_message::fields_type, rpt_seq) == 52, "unexpected offset of trade_53_message::fields_type::rpt_seq");
static_assert(sizeof(trade_53_message::fields_type) == 56, "unexpected sizeof trade_53_message::fields_type");
static_assert(sizeof(trade_53_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 56, "unexpected sizeof trade_53_message");

#pragma pack(pop)
}
