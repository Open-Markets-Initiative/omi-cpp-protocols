#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Quantity.hpp"
#include "../types/ComplexInstrumentId.hpp"
#include "../types/Price.hpp"
#include "../types/Padding.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Add Order Long Message
struct add_order_long_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::order_id order_id;
        pitch_complex::side_indicator side_indicator;
        pitch_complex::quantity quantity;
        pitch_complex::complex_instrument_id complex_instrument_id;
        pitch_complex::price price;
        pitch_complex::padding padding;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::add_order_long_message};

    fields_type fields;

    // parse method
    static add_order_long_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_long_message*>(buffer);
    }

    // parse method const
    static const add_order_long_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_long_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_long_message::fields_type, time_offset) == 0, "unexpected offset of add_order_long_message::fields_type::time_offset");
static_assert(offsetof(add_order_long_message::fields_type, order_id) == 4, "unexpected offset of add_order_long_message::fields_type::order_id");
static_assert(offsetof(add_order_long_message::fields_type, side_indicator) == 12, "unexpected offset of add_order_long_message::fields_type::side_indicator");
static_assert(offsetof(add_order_long_message::fields_type, quantity) == 13, "unexpected offset of add_order_long_message::fields_type::quantity");
static_assert(offsetof(add_order_long_message::fields_type, complex_instrument_id) == 17, "unexpected offset of add_order_long_message::fields_type::complex_instrument_id");
static_assert(offsetof(add_order_long_message::fields_type, price) == 23, "unexpected offset of add_order_long_message::fields_type::price");
static_assert(offsetof(add_order_long_message::fields_type, padding) == 31, "unexpected offset of add_order_long_message::fields_type::padding");
static_assert(sizeof(add_order_long_message::fields_type) == 32, "unexpected sizeof add_order_long_message::fields_type");
static_assert(sizeof(add_order_long_message) == sizeof(pitch_complex::message_header) + 32, "unexpected sizeof add_order_long_message");

#pragma pack(pop)
}
