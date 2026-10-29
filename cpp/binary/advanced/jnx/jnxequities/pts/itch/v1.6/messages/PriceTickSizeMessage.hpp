#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/PriceTickSizeTableId.hpp"
#include "../types/PriceTickSize.hpp"
#include "../types/PriceStart.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

namespace itch_pts = ::jnx::jnxequities::pts::itch::v1_6;

#pragma pack(push, 1)

// Price Tick Size Message
struct price_tick_size_message {

    struct fields_type {
        itch_pts::nanoseconds nanoseconds;
        itch_pts::price_tick_size_table_id price_tick_size_table_id;
        itch_pts::price_tick_size price_tick_size;
        itch_pts::price_start price_start;
    };

    itch_pts::message_header header = {std::uint16_t(sizeof(itch_pts::message_header) + sizeof(fields_type) - 2), message_type::enum_type::price_tick_size_message};

    fields_type fields;

    // parse method
    static price_tick_size_message* parse(std::byte* buffer) {
        return reinterpret_cast<price_tick_size_message*>(buffer);
    }

    // parse method const
    static const price_tick_size_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const price_tick_size_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(price_tick_size_message::fields_type, nanoseconds) == 0, "unexpected offset of price_tick_size_message::fields_type::nanoseconds");
static_assert(offsetof(price_tick_size_message::fields_type, price_tick_size_table_id) == 4, "unexpected offset of price_tick_size_message::fields_type::price_tick_size_table_id");
static_assert(offsetof(price_tick_size_message::fields_type, price_tick_size) == 8, "unexpected offset of price_tick_size_message::fields_type::price_tick_size");
static_assert(offsetof(price_tick_size_message::fields_type, price_start) == 12, "unexpected offset of price_tick_size_message::fields_type::price_start");
static_assert(sizeof(price_tick_size_message::fields_type) == 16, "unexpected sizeof price_tick_size_message::fields_type");
static_assert(sizeof(price_tick_size_message) == sizeof(itch_pts::message_header) + 16, "unexpected sizeof price_tick_size_message");

#pragma pack(pop)
}
