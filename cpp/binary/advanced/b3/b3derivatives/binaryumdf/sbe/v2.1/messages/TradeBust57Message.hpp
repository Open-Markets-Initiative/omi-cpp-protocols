#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/Offset10Padding2.hpp"
#include "../types/MdFuturePrice.hpp"
#include "../types/MdEntrySizeQuantity.hpp"
#include "../types/TradeId.hpp"
#include "../types/TradeDate.hpp"
#include "../types/Offset34Padding2.hpp"
#include "../types/TransactTime.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_1;

#pragma pack(push, 1)

// Trade Bust 57 Message
struct trade_bust_57_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::trading_session_id trading_session_id;
        sbe_binaryumdf::offset_10_padding_2 offset_10_padding_2;
        sbe_binaryumdf::md_future_price md_future_price;
        sbe_binaryumdf::md_entry_size_quantity md_entry_size_quantity;
        sbe_binaryumdf::trade_id trade_id;
        sbe_binaryumdf::trade_date trade_date;
        sbe_binaryumdf::offset_34_padding_2 offset_34_padding_2;
        sbe_binaryumdf::transact_time transact_time;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static trade_bust_57_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_bust_57_message*>(buffer);
    }

    // parse method const
    static const trade_bust_57_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_bust_57_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_bust_57_message::fields_type, security_id) == 0, "unexpected offset of trade_bust_57_message::fields_type::security_id");
static_assert(offsetof(trade_bust_57_message::fields_type, match_event_indicator) == 8, "unexpected offset of trade_bust_57_message::fields_type::match_event_indicator");
static_assert(offsetof(trade_bust_57_message::fields_type, trading_session_id) == 9, "unexpected offset of trade_bust_57_message::fields_type::trading_session_id");
static_assert(offsetof(trade_bust_57_message::fields_type, offset_10_padding_2) == 10, "unexpected offset of trade_bust_57_message::fields_type::offset_10_padding_2");
static_assert(offsetof(trade_bust_57_message::fields_type, md_future_price) == 12, "unexpected offset of trade_bust_57_message::fields_type::md_future_price");
static_assert(offsetof(trade_bust_57_message::fields_type, md_entry_size_quantity) == 20, "unexpected offset of trade_bust_57_message::fields_type::md_entry_size_quantity");
static_assert(offsetof(trade_bust_57_message::fields_type, trade_id) == 28, "unexpected offset of trade_bust_57_message::fields_type::trade_id");
static_assert(offsetof(trade_bust_57_message::fields_type, trade_date) == 32, "unexpected offset of trade_bust_57_message::fields_type::trade_date");
static_assert(offsetof(trade_bust_57_message::fields_type, offset_34_padding_2) == 34, "unexpected offset of trade_bust_57_message::fields_type::offset_34_padding_2");
static_assert(offsetof(trade_bust_57_message::fields_type, transact_time) == 36, "unexpected offset of trade_bust_57_message::fields_type::transact_time");
static_assert(offsetof(trade_bust_57_message::fields_type, rpt_seq) == 44, "unexpected offset of trade_bust_57_message::fields_type::rpt_seq");
static_assert(sizeof(trade_bust_57_message::fields_type) == 48, "unexpected sizeof trade_bust_57_message::fields_type");
static_assert(sizeof(trade_bust_57_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 48, "unexpected sizeof trade_bust_57_message");

#pragma pack(pop)
}
