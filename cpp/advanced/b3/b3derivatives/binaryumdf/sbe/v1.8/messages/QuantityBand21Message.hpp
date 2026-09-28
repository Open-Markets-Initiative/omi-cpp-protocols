#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Offset9Padding3.hpp"
#include "../types/AvgDailyTradedQty.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_8;

#pragma pack(push, 1)

// Quantity Band 21 Message
struct quantity_band_21_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::offset_9_padding_3 offset_9_padding_3;
        sbe_binaryumdf::avg_daily_traded_qty avg_daily_traded_qty;
        sbe_binaryumdf::max_trade_vol max_trade_vol;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static quantity_band_21_message* parse(std::byte* buffer) {
        return reinterpret_cast<quantity_band_21_message*>(buffer);
    }

    // parse method const
    static const quantity_band_21_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quantity_band_21_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quantity_band_21_message::fields_type, security_id) == 0, "unexpected offset of quantity_band_21_message::fields_type::security_id");
static_assert(offsetof(quantity_band_21_message::fields_type, match_event_indicator) == 8, "unexpected offset of quantity_band_21_message::fields_type::match_event_indicator");
static_assert(offsetof(quantity_band_21_message::fields_type, offset_9_padding_3) == 9, "unexpected offset of quantity_band_21_message::fields_type::offset_9_padding_3");
static_assert(offsetof(quantity_band_21_message::fields_type, avg_daily_traded_qty) == 12, "unexpected offset of quantity_band_21_message::fields_type::avg_daily_traded_qty");
static_assert(offsetof(quantity_band_21_message::fields_type, max_trade_vol) == 20, "unexpected offset of quantity_band_21_message::fields_type::max_trade_vol");
static_assert(offsetof(quantity_band_21_message::fields_type, md_entry_timestamp) == 28, "unexpected offset of quantity_band_21_message::fields_type::md_entry_timestamp");
static_assert(offsetof(quantity_band_21_message::fields_type, rpt_seq) == 36, "unexpected offset of quantity_band_21_message::fields_type::rpt_seq");
static_assert(sizeof(quantity_band_21_message::fields_type) == 40, "unexpected sizeof quantity_band_21_message::fields_type");
static_assert(sizeof(quantity_band_21_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 40, "unexpected sizeof quantity_band_21_message");

#pragma pack(pop)
}
