#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderBookPosition.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../types/OrderAttributes.hpp"
#include "../types/LotType.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Add Order No Mpid
struct add_order_no_mpid {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::order_id order_id;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::side side;
        itch_geniuminet::order_book_position order_book_position;
        itch_geniuminet::quantity quantity;
        itch_geniuminet::price price;
        itch_geniuminet::order_attributes order_attributes;
        itch_geniuminet::lot_type lot_type;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::add_order_no_mpid};

    fields_type fields;

    // parse method
    static add_order_no_mpid* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_no_mpid*>(buffer);
    }

    // parse method const
    static const add_order_no_mpid* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_no_mpid*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_no_mpid::fields_type, nanoseconds) == 0, "unexpected offset of add_order_no_mpid::fields_type::nanoseconds");
static_assert(offsetof(add_order_no_mpid::fields_type, order_id) == 4, "unexpected offset of add_order_no_mpid::fields_type::order_id");
static_assert(offsetof(add_order_no_mpid::fields_type, order_book_id) == 12, "unexpected offset of add_order_no_mpid::fields_type::order_book_id");
static_assert(offsetof(add_order_no_mpid::fields_type, side) == 16, "unexpected offset of add_order_no_mpid::fields_type::side");
static_assert(offsetof(add_order_no_mpid::fields_type, order_book_position) == 17, "unexpected offset of add_order_no_mpid::fields_type::order_book_position");
static_assert(offsetof(add_order_no_mpid::fields_type, quantity) == 21, "unexpected offset of add_order_no_mpid::fields_type::quantity");
static_assert(offsetof(add_order_no_mpid::fields_type, price) == 29, "unexpected offset of add_order_no_mpid::fields_type::price");
static_assert(offsetof(add_order_no_mpid::fields_type, order_attributes) == 33, "unexpected offset of add_order_no_mpid::fields_type::order_attributes");
static_assert(offsetof(add_order_no_mpid::fields_type, lot_type) == 35, "unexpected offset of add_order_no_mpid::fields_type::lot_type");
static_assert(sizeof(add_order_no_mpid::fields_type) == 36, "unexpected sizeof add_order_no_mpid::fields_type");
static_assert(sizeof(add_order_no_mpid) == sizeof(itch_geniuminet::message_header) + 36, "unexpected sizeof add_order_no_mpid");

#pragma pack(pop)
}
