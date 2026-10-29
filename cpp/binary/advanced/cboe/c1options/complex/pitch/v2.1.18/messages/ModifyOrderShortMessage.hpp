#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/QuantityShort.hpp"
#include "../types/PriceShort.hpp"
#include "../types/Padding.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Modify Order Short Message
struct modify_order_short_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::order_id order_id;
        pitch_complex::quantity_short quantity_short;
        pitch_complex::price_short price_short;
        pitch_complex::padding padding;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::modify_order_short_message};

    fields_type fields;

    // parse method
    static modify_order_short_message* parse(std::byte* buffer) {
        return reinterpret_cast<modify_order_short_message*>(buffer);
    }

    // parse method const
    static const modify_order_short_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const modify_order_short_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(modify_order_short_message::fields_type, time_offset) == 0, "unexpected offset of modify_order_short_message::fields_type::time_offset");
static_assert(offsetof(modify_order_short_message::fields_type, order_id) == 4, "unexpected offset of modify_order_short_message::fields_type::order_id");
static_assert(offsetof(modify_order_short_message::fields_type, quantity_short) == 12, "unexpected offset of modify_order_short_message::fields_type::quantity_short");
static_assert(offsetof(modify_order_short_message::fields_type, price_short) == 14, "unexpected offset of modify_order_short_message::fields_type::price_short");
static_assert(offsetof(modify_order_short_message::fields_type, padding) == 16, "unexpected offset of modify_order_short_message::fields_type::padding");
static_assert(sizeof(modify_order_short_message::fields_type) == 17, "unexpected sizeof modify_order_short_message::fields_type");
static_assert(sizeof(modify_order_short_message) == sizeof(pitch_complex::message_header) + 17, "unexpected sizeof modify_order_short_message");

#pragma pack(pop)
}
