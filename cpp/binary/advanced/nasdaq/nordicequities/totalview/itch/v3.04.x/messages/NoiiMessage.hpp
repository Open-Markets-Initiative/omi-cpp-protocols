#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/PairedQuantity.hpp"
#include "../types/ImbalanceQuantity.hpp"
#include "../types/ImbalanceDirection.hpp"
#include "../types/OrderBook.hpp"
#include "../types/EquilibriumPrice.hpp"
#include "../types/CrossType.hpp"
#include "../types/BestBidPrice.hpp"
#include "../types/BestBidQuantity.hpp"
#include "../types/BestAskPrice.hpp"
#include "../types/BestAskQuantity.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Noii Message
struct noii_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::paired_quantity paired_quantity;
        itch_totalview::imbalance_quantity imbalance_quantity;
        itch_totalview::imbalance_direction imbalance_direction;
        itch_totalview::order_book order_book;
        itch_totalview::equilibrium_price equilibrium_price;
        itch_totalview::cross_type cross_type;
        itch_totalview::best_bid_price best_bid_price;
        itch_totalview::best_bid_quantity best_bid_quantity;
        itch_totalview::best_ask_price best_ask_price;
        itch_totalview::best_ask_quantity best_ask_quantity;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::noii_message};

    fields_type fields;

    // parse method
    static noii_message* parse(std::byte* buffer) {
        return reinterpret_cast<noii_message*>(buffer);
    }

    // parse method const
    static const noii_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const noii_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(noii_message::fields_type, timestamp) == 0, "unexpected offset of noii_message::fields_type::timestamp");
static_assert(offsetof(noii_message::fields_type, tracking_number) == 8, "unexpected offset of noii_message::fields_type::tracking_number");
static_assert(offsetof(noii_message::fields_type, paired_quantity) == 10, "unexpected offset of noii_message::fields_type::paired_quantity");
static_assert(offsetof(noii_message::fields_type, imbalance_quantity) == 18, "unexpected offset of noii_message::fields_type::imbalance_quantity");
static_assert(offsetof(noii_message::fields_type, imbalance_direction) == 26, "unexpected offset of noii_message::fields_type::imbalance_direction");
static_assert(offsetof(noii_message::fields_type, order_book) == 27, "unexpected offset of noii_message::fields_type::order_book");
static_assert(offsetof(noii_message::fields_type, equilibrium_price) == 31, "unexpected offset of noii_message::fields_type::equilibrium_price");
static_assert(offsetof(noii_message::fields_type, cross_type) == 35, "unexpected offset of noii_message::fields_type::cross_type");
static_assert(offsetof(noii_message::fields_type, best_bid_price) == 36, "unexpected offset of noii_message::fields_type::best_bid_price");
static_assert(offsetof(noii_message::fields_type, best_bid_quantity) == 40, "unexpected offset of noii_message::fields_type::best_bid_quantity");
static_assert(offsetof(noii_message::fields_type, best_ask_price) == 48, "unexpected offset of noii_message::fields_type::best_ask_price");
static_assert(offsetof(noii_message::fields_type, best_ask_quantity) == 52, "unexpected offset of noii_message::fields_type::best_ask_quantity");
static_assert(sizeof(noii_message::fields_type) == 60, "unexpected sizeof noii_message::fields_type");
static_assert(sizeof(noii_message) == sizeof(itch_totalview::message_header) + 60, "unexpected sizeof noii_message");

#pragma pack(pop)
}
