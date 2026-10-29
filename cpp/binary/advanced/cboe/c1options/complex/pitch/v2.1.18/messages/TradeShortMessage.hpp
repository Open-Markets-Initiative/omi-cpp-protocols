#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityShort.hpp"
#include "../types/ComplexInstrumentId.hpp"
#include "../types/PriceShort.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/TradeCondition.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Trade Short Message
struct trade_short_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::order_id order_id;
        pitch_complex::side_indicator side_indicator;
        pitch_complex::quantity_short quantity_short;
        pitch_complex::complex_instrument_id complex_instrument_id;
        pitch_complex::price_short price_short;
        pitch_complex::execution_id execution_id;
        pitch_complex::trade_condition trade_condition;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::trade_short_message};

    fields_type fields;

    // parse method
    static trade_short_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_short_message*>(buffer);
    }

    // parse method const
    static const trade_short_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_short_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_short_message::fields_type, time_offset) == 0, "unexpected offset of trade_short_message::fields_type::time_offset");
static_assert(offsetof(trade_short_message::fields_type, order_id) == 4, "unexpected offset of trade_short_message::fields_type::order_id");
static_assert(offsetof(trade_short_message::fields_type, side_indicator) == 12, "unexpected offset of trade_short_message::fields_type::side_indicator");
static_assert(offsetof(trade_short_message::fields_type, quantity_short) == 13, "unexpected offset of trade_short_message::fields_type::quantity_short");
static_assert(offsetof(trade_short_message::fields_type, complex_instrument_id) == 15, "unexpected offset of trade_short_message::fields_type::complex_instrument_id");
static_assert(offsetof(trade_short_message::fields_type, price_short) == 21, "unexpected offset of trade_short_message::fields_type::price_short");
static_assert(offsetof(trade_short_message::fields_type, execution_id) == 23, "unexpected offset of trade_short_message::fields_type::execution_id");
static_assert(offsetof(trade_short_message::fields_type, trade_condition) == 31, "unexpected offset of trade_short_message::fields_type::trade_condition");
static_assert(sizeof(trade_short_message::fields_type) == 32, "unexpected sizeof trade_short_message::fields_type");
static_assert(sizeof(trade_short_message) == sizeof(pitch_complex::message_header) + 32, "unexpected sizeof trade_short_message");

#pragma pack(pop)
}
