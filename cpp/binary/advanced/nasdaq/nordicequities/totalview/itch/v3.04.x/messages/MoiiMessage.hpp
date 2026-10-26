#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/PairedQuantity.hpp"
#include "../types/OrderBook.hpp"
#include "../types/EquilibriumPrice.hpp"
#include "../types/CrossType.hpp"
#include "../types/CrossLevel.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Moii Message
struct moii_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::paired_quantity paired_quantity;
        itch_totalview::order_book order_book;
        itch_totalview::equilibrium_price equilibrium_price;
        itch_totalview::cross_type cross_type;
        itch_totalview::cross_level cross_level;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::moii_message};

    fields_type fields;

    // parse method
    static moii_message* parse(std::byte* buffer) {
        return reinterpret_cast<moii_message*>(buffer);
    }

    // parse method const
    static const moii_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const moii_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(moii_message::fields_type, timestamp) == 0, "unexpected offset of moii_message::fields_type::timestamp");
static_assert(offsetof(moii_message::fields_type, tracking_number) == 8, "unexpected offset of moii_message::fields_type::tracking_number");
static_assert(offsetof(moii_message::fields_type, paired_quantity) == 10, "unexpected offset of moii_message::fields_type::paired_quantity");
static_assert(offsetof(moii_message::fields_type, order_book) == 18, "unexpected offset of moii_message::fields_type::order_book");
static_assert(offsetof(moii_message::fields_type, equilibrium_price) == 22, "unexpected offset of moii_message::fields_type::equilibrium_price");
static_assert(offsetof(moii_message::fields_type, cross_type) == 26, "unexpected offset of moii_message::fields_type::cross_type");
static_assert(offsetof(moii_message::fields_type, cross_level) == 27, "unexpected offset of moii_message::fields_type::cross_level");
static_assert(sizeof(moii_message::fields_type) == 28, "unexpected sizeof moii_message::fields_type");
static_assert(sizeof(moii_message) == sizeof(itch_totalview::message_header) + 28, "unexpected sizeof moii_message");

#pragma pack(pop)
}
