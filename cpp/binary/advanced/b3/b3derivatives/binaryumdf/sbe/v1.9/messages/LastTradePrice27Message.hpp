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
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"
#include "../types/SellerDays.hpp"
#include "../types/MdEntryInterestRate.hpp"
#include "../types/TrdSubType.hpp"
#include "../types/Padding3.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_9;

#pragma pack(push, 1)

// Last Trade Price 27 Message
struct last_trade_price_27_message {

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
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
        sbe_binaryumdf::seller_days seller_days;
        sbe_binaryumdf::md_entry_interest_rate md_entry_interest_rate;
        sbe_binaryumdf::trd_sub_type trd_sub_type;
        sbe_binaryumdf::padding_3 padding_3;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static last_trade_price_27_message* parse(std::byte* buffer) {
        return reinterpret_cast<last_trade_price_27_message*>(buffer);
    }

    // parse method const
    static const last_trade_price_27_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const last_trade_price_27_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(last_trade_price_27_message::fields_type, security_id) == 0, "unexpected offset of last_trade_price_27_message::fields_type::security_id");
static_assert(offsetof(last_trade_price_27_message::fields_type, match_event_indicator) == 8, "unexpected offset of last_trade_price_27_message::fields_type::match_event_indicator");
static_assert(offsetof(last_trade_price_27_message::fields_type, trading_session_id) == 9, "unexpected offset of last_trade_price_27_message::fields_type::trading_session_id");
static_assert(offsetof(last_trade_price_27_message::fields_type, trade_condition) == 10, "unexpected offset of last_trade_price_27_message::fields_type::trade_condition");
static_assert(offsetof(last_trade_price_27_message::fields_type, md_future_price) == 12, "unexpected offset of last_trade_price_27_message::fields_type::md_future_price");
static_assert(offsetof(last_trade_price_27_message::fields_type, md_entry_size_quantity) == 20, "unexpected offset of last_trade_price_27_message::fields_type::md_entry_size_quantity");
static_assert(offsetof(last_trade_price_27_message::fields_type, trade_id) == 28, "unexpected offset of last_trade_price_27_message::fields_type::trade_id");
static_assert(offsetof(last_trade_price_27_message::fields_type, md_entry_buyer) == 32, "unexpected offset of last_trade_price_27_message::fields_type::md_entry_buyer");
static_assert(offsetof(last_trade_price_27_message::fields_type, md_entry_seller) == 36, "unexpected offset of last_trade_price_27_message::fields_type::md_entry_seller");
static_assert(offsetof(last_trade_price_27_message::fields_type, trade_date) == 40, "unexpected offset of last_trade_price_27_message::fields_type::trade_date");
static_assert(offsetof(last_trade_price_27_message::fields_type, md_entry_timestamp) == 42, "unexpected offset of last_trade_price_27_message::fields_type::md_entry_timestamp");
static_assert(offsetof(last_trade_price_27_message::fields_type, rpt_seq) == 50, "unexpected offset of last_trade_price_27_message::fields_type::rpt_seq");
static_assert(offsetof(last_trade_price_27_message::fields_type, seller_days) == 54, "unexpected offset of last_trade_price_27_message::fields_type::seller_days");
static_assert(offsetof(last_trade_price_27_message::fields_type, md_entry_interest_rate) == 56, "unexpected offset of last_trade_price_27_message::fields_type::md_entry_interest_rate");
static_assert(offsetof(last_trade_price_27_message::fields_type, trd_sub_type) == 64, "unexpected offset of last_trade_price_27_message::fields_type::trd_sub_type");
static_assert(offsetof(last_trade_price_27_message::fields_type, padding_3) == 65, "unexpected offset of last_trade_price_27_message::fields_type::padding_3");
static_assert(sizeof(last_trade_price_27_message::fields_type) == 68, "unexpected sizeof last_trade_price_27_message::fields_type");
static_assert(sizeof(last_trade_price_27_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 68, "unexpected sizeof last_trade_price_27_message");

#pragma pack(pop)
}
