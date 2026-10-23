#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/AvailableBidQuantityAtEquilibriumPrice.hpp"
#include "../types/AvailableAskQuantityAtEquilibriumPrice.hpp"
#include "../types/EquilibriumPrice.hpp"
#include "../types/Reserved24.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

namespace itch_geniuminet = ::jpx::osederivatives::geniuminet::itch::v5_0_6;

#pragma pack(push, 1)

// Equilibrium Price Update
struct equilibrium_price_update {

    struct fields_type {
        itch_geniuminet::nanoseconds nanoseconds;
        itch_geniuminet::order_book_id order_book_id;
        itch_geniuminet::available_bid_quantity_at_equilibrium_price available_bid_quantity_at_equilibrium_price;
        itch_geniuminet::available_ask_quantity_at_equilibrium_price available_ask_quantity_at_equilibrium_price;
        itch_geniuminet::equilibrium_price equilibrium_price;
        itch_geniuminet::reserved_24 reserved_24;
    };

    itch_geniuminet::message_header header = {std::uint16_t(sizeof(itch_geniuminet::message_header) + sizeof(fields_type) - 2), message_type::enum_type::equilibrium_price_update};

    fields_type fields;

    // parse method
    static equilibrium_price_update* parse(std::byte* buffer) {
        return reinterpret_cast<equilibrium_price_update*>(buffer);
    }

    // parse method const
    static const equilibrium_price_update* parse(const std::byte* buffer) {
        return reinterpret_cast<const equilibrium_price_update*>(buffer);
    }

};

// layout verification
static_assert(offsetof(equilibrium_price_update::fields_type, nanoseconds) == 0, "unexpected offset of equilibrium_price_update::fields_type::nanoseconds");
static_assert(offsetof(equilibrium_price_update::fields_type, order_book_id) == 4, "unexpected offset of equilibrium_price_update::fields_type::order_book_id");
static_assert(offsetof(equilibrium_price_update::fields_type, available_bid_quantity_at_equilibrium_price) == 8, "unexpected offset of equilibrium_price_update::fields_type::available_bid_quantity_at_equilibrium_price");
static_assert(offsetof(equilibrium_price_update::fields_type, available_ask_quantity_at_equilibrium_price) == 16, "unexpected offset of equilibrium_price_update::fields_type::available_ask_quantity_at_equilibrium_price");
static_assert(offsetof(equilibrium_price_update::fields_type, equilibrium_price) == 24, "unexpected offset of equilibrium_price_update::fields_type::equilibrium_price");
static_assert(offsetof(equilibrium_price_update::fields_type, reserved_24) == 28, "unexpected offset of equilibrium_price_update::fields_type::reserved_24");
static_assert(sizeof(equilibrium_price_update::fields_type) == 52, "unexpected sizeof equilibrium_price_update::fields_type");
static_assert(sizeof(equilibrium_price_update) == sizeof(itch_geniuminet::message_header) + 52, "unexpected sizeof equilibrium_price_update");

#pragma pack(pop)
}
