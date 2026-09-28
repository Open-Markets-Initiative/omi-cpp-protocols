#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/PriceBandType.hpp"
#include "../types/PriceLimitType.hpp"
#include "../types/PriceBandMidpointPriceType.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../types/MdEntryTimestamp.hpp"
#include "../types/RptSeq.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_2;

#pragma pack(push, 1)

// Price Band 22 Message
struct price_band_22_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::price_band_type price_band_type;
        sbe_binaryumdf::price_limit_type price_limit_type;
        sbe_binaryumdf::price_band_midpoint_price_type price_band_midpoint_price_type;
        sbe_binaryumdf::low_limit_price low_limit_price;
        sbe_binaryumdf::high_limit_price high_limit_price;
        sbe_binaryumdf::trading_reference_price trading_reference_price;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
        sbe_binaryumdf::rpt_seq rpt_seq;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static price_band_22_message* parse(std::byte* buffer) {
        return reinterpret_cast<price_band_22_message*>(buffer);
    }

    // parse method const
    static const price_band_22_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const price_band_22_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(price_band_22_message::fields_type, security_id) == 0, "unexpected offset of price_band_22_message::fields_type::security_id");
static_assert(offsetof(price_band_22_message::fields_type, match_event_indicator) == 8, "unexpected offset of price_band_22_message::fields_type::match_event_indicator");
static_assert(offsetof(price_band_22_message::fields_type, price_band_type) == 9, "unexpected offset of price_band_22_message::fields_type::price_band_type");
static_assert(offsetof(price_band_22_message::fields_type, price_limit_type) == 10, "unexpected offset of price_band_22_message::fields_type::price_limit_type");
static_assert(offsetof(price_band_22_message::fields_type, price_band_midpoint_price_type) == 11, "unexpected offset of price_band_22_message::fields_type::price_band_midpoint_price_type");
static_assert(offsetof(price_band_22_message::fields_type, low_limit_price) == 12, "unexpected offset of price_band_22_message::fields_type::low_limit_price");
static_assert(offsetof(price_band_22_message::fields_type, high_limit_price) == 20, "unexpected offset of price_band_22_message::fields_type::high_limit_price");
static_assert(offsetof(price_band_22_message::fields_type, trading_reference_price) == 28, "unexpected offset of price_band_22_message::fields_type::trading_reference_price");
static_assert(offsetof(price_band_22_message::fields_type, md_entry_timestamp) == 36, "unexpected offset of price_band_22_message::fields_type::md_entry_timestamp");
static_assert(offsetof(price_band_22_message::fields_type, rpt_seq) == 44, "unexpected offset of price_band_22_message::fields_type::rpt_seq");
static_assert(sizeof(price_band_22_message::fields_type) == 48, "unexpected sizeof price_band_22_message::fields_type");
static_assert(sizeof(price_band_22_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 48, "unexpected sizeof price_band_22_message");

#pragma pack(pop)
}
