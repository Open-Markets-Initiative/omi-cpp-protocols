#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/SecuritySymbol.hpp"
#include "../types/ExpirationDate.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/CallOrPut.hpp"
#include "../types/OpeningTime.hpp"
#include "../types/ClosingTime.hpp"
#include "../types/RestrictedOption.hpp"
#include "../types/LongTermOption.hpp"
#include "../types/ActiveOnMiax.hpp"
#include "../types/MiaxBboPostingIncrementIndicator.hpp"
#include "../types/LiquidityAcceptanceIncrementIndicator.hpp"
#include "../types/OpeningUnderlyingMarketCode.hpp"
#include "../types/PriorityQuoteWidth.hpp"
#include "../types/Reserved8.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// Simple Series Update Message
struct simple_series_update_message {

    struct fields_type {
        mach_topofmarket::nanoseconds nanoseconds;
        mach_topofmarket::product_id product_id;
        mach_topofmarket::underlying_symbol underlying_symbol;
        mach_topofmarket::security_symbol security_symbol;
        mach_topofmarket::expiration_date expiration_date;
        mach_topofmarket::strike_price strike_price;
        mach_topofmarket::call_or_put call_or_put;
        mach_topofmarket::opening_time opening_time;
        mach_topofmarket::closing_time closing_time;
        mach_topofmarket::restricted_option restricted_option;
        mach_topofmarket::long_term_option long_term_option;
        mach_topofmarket::active_on_miax active_on_miax;
        mach_topofmarket::miax_bbo_posting_increment_indicator miax_bbo_posting_increment_indicator;
        mach_topofmarket::liquidity_acceptance_increment_indicator liquidity_acceptance_increment_indicator;
        mach_topofmarket::opening_underlying_market_code opening_underlying_market_code;
        mach_topofmarket::priority_quote_width priority_quote_width;
        mach_topofmarket::reserved_8 reserved_8;
    };

    mach_topofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_topofmarket::packet_length packet_length;
    mach_topofmarket::packet_type packet_type = mach_topofmarket::packet_type::enum_type::application_message;
    mach_topofmarket::session_number session_number;
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::simple_series_update_message;

    fields_type fields;

    // parse method
    static simple_series_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<simple_series_update_message*>(buffer);
    }

    // parse method const
    static const simple_series_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const simple_series_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(simple_series_update_message::fields_type, nanoseconds) == 0, "unexpected offset of simple_series_update_message::fields_type::nanoseconds");
static_assert(offsetof(simple_series_update_message::fields_type, product_id) == 4, "unexpected offset of simple_series_update_message::fields_type::product_id");
static_assert(offsetof(simple_series_update_message::fields_type, underlying_symbol) == 8, "unexpected offset of simple_series_update_message::fields_type::underlying_symbol");
static_assert(offsetof(simple_series_update_message::fields_type, security_symbol) == 19, "unexpected offset of simple_series_update_message::fields_type::security_symbol");
static_assert(offsetof(simple_series_update_message::fields_type, expiration_date) == 25, "unexpected offset of simple_series_update_message::fields_type::expiration_date");
static_assert(offsetof(simple_series_update_message::fields_type, strike_price) == 33, "unexpected offset of simple_series_update_message::fields_type::strike_price");
static_assert(offsetof(simple_series_update_message::fields_type, call_or_put) == 37, "unexpected offset of simple_series_update_message::fields_type::call_or_put");
static_assert(offsetof(simple_series_update_message::fields_type, opening_time) == 38, "unexpected offset of simple_series_update_message::fields_type::opening_time");
static_assert(offsetof(simple_series_update_message::fields_type, closing_time) == 46, "unexpected offset of simple_series_update_message::fields_type::closing_time");
static_assert(offsetof(simple_series_update_message::fields_type, restricted_option) == 54, "unexpected offset of simple_series_update_message::fields_type::restricted_option");
static_assert(offsetof(simple_series_update_message::fields_type, long_term_option) == 55, "unexpected offset of simple_series_update_message::fields_type::long_term_option");
static_assert(offsetof(simple_series_update_message::fields_type, active_on_miax) == 56, "unexpected offset of simple_series_update_message::fields_type::active_on_miax");
static_assert(offsetof(simple_series_update_message::fields_type, miax_bbo_posting_increment_indicator) == 57, "unexpected offset of simple_series_update_message::fields_type::miax_bbo_posting_increment_indicator");
static_assert(offsetof(simple_series_update_message::fields_type, liquidity_acceptance_increment_indicator) == 58, "unexpected offset of simple_series_update_message::fields_type::liquidity_acceptance_increment_indicator");
static_assert(offsetof(simple_series_update_message::fields_type, opening_underlying_market_code) == 59, "unexpected offset of simple_series_update_message::fields_type::opening_underlying_market_code");
static_assert(offsetof(simple_series_update_message::fields_type, priority_quote_width) == 60, "unexpected offset of simple_series_update_message::fields_type::priority_quote_width");
static_assert(offsetof(simple_series_update_message::fields_type, reserved_8) == 64, "unexpected offset of simple_series_update_message::fields_type::reserved_8");
static_assert(sizeof(simple_series_update_message::fields_type) == 72, "unexpected sizeof simple_series_update_message::fields_type");
static_assert(sizeof(simple_series_update_message) == sizeof(mach_topofmarket::sequence_number) + sizeof(mach_topofmarket::packet_length) + sizeof(mach_topofmarket::packet_type) + sizeof(mach_topofmarket::session_number) + sizeof(mach_topofmarket::message_type) + 72, "unexpected sizeof simple_series_update_message");

#pragma pack(pop)
}
