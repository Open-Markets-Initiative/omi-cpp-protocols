#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/TickSize.hpp"
#include "../types/PriceFrom.hpp"
#include "../types/PriceTo.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Tick Size Table Entry
struct tick_size_table_entry {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::tick_size tick_size;
        itch_geniuminet::price_from price_from;
        itch_geniuminet::price_to price_to;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::tick_size_table_entry};

    fields_type fields;

    // parse method
    static tick_size_table_entry* parse(std::byte* buffer) {
        return reinterpret_cast<tick_size_table_entry*>(buffer);
    }

    // parse method const
    static const tick_size_table_entry* parse(const std::byte* buffer) {
        return reinterpret_cast<const tick_size_table_entry*>(buffer);
    }

};

// layout verification
static_assert(offsetof(tick_size_table_entry::fields_type, nanoseconds) == 0, "unexpected offset of tick_size_table_entry::fields_type::nanoseconds");
static_assert(offsetof(tick_size_table_entry::fields_type, order_book_id) == 4, "unexpected offset of tick_size_table_entry::fields_type::order_book_id");
static_assert(offsetof(tick_size_table_entry::fields_type, tick_size) == 8, "unexpected offset of tick_size_table_entry::fields_type::tick_size");
static_assert(offsetof(tick_size_table_entry::fields_type, price_from) == 16, "unexpected offset of tick_size_table_entry::fields_type::price_from");
static_assert(offsetof(tick_size_table_entry::fields_type, price_to) == 20, "unexpected offset of tick_size_table_entry::fields_type::price_to");
static_assert(sizeof(tick_size_table_entry::fields_type) == 24, "unexpected sizeof tick_size_table_entry::fields_type");
static_assert(sizeof(tick_size_table_entry) == sizeof(itch_geniuminet::message_header) + 24, "unexpected sizeof tick_size_table_entry");

#pragma pack(pop)
}
