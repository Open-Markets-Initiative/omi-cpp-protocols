#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/PairedShares.hpp"
#include "../types/ImbalanceShares.hpp"
#include "../types/ImbalanceDirection.hpp"
#include "../types/Stock.hpp"
#include "../types/FarPrice.hpp"
#include "../types/NearPrice.hpp"
#include "../types/CurrentReferencePrice.hpp"
#include "../types/CrossType.hpp"
#include "../types/PriceVariationIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Net Order Imbalance Indicator Message
struct net_order_imbalance_indicator_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::paired_shares paired_shares;
        itch_totalview::imbalance_shares imbalance_shares;
        itch_totalview::imbalance_direction imbalance_direction;
        itch_totalview::stock stock;
        itch_totalview::far_price far_price;
        itch_totalview::near_price near_price;
        itch_totalview::current_reference_price current_reference_price;
        itch_totalview::cross_type cross_type;
        itch_totalview::price_variation_indicator price_variation_indicator;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::net_order_imbalance_indicator_message};

    fields_type fields;

    // parse method
    static net_order_imbalance_indicator_message* parse(std::byte* buffer) {
        return reinterpret_cast<net_order_imbalance_indicator_message*>(buffer);
    }

    // parse method const
    static const net_order_imbalance_indicator_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const net_order_imbalance_indicator_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, nanoseconds) == 0, "unexpected offset of net_order_imbalance_indicator_message::fields_type::nanoseconds");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, paired_shares) == 4, "unexpected offset of net_order_imbalance_indicator_message::fields_type::paired_shares");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, imbalance_shares) == 12, "unexpected offset of net_order_imbalance_indicator_message::fields_type::imbalance_shares");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, imbalance_direction) == 20, "unexpected offset of net_order_imbalance_indicator_message::fields_type::imbalance_direction");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, stock) == 21, "unexpected offset of net_order_imbalance_indicator_message::fields_type::stock");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, far_price) == 27, "unexpected offset of net_order_imbalance_indicator_message::fields_type::far_price");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, near_price) == 31, "unexpected offset of net_order_imbalance_indicator_message::fields_type::near_price");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, current_reference_price) == 35, "unexpected offset of net_order_imbalance_indicator_message::fields_type::current_reference_price");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, cross_type) == 39, "unexpected offset of net_order_imbalance_indicator_message::fields_type::cross_type");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, price_variation_indicator) == 40, "unexpected offset of net_order_imbalance_indicator_message::fields_type::price_variation_indicator");
static_assert(sizeof(net_order_imbalance_indicator_message::fields_type) == 41, "unexpected sizeof net_order_imbalance_indicator_message::fields_type");
static_assert(sizeof(net_order_imbalance_indicator_message) == sizeof(itch_totalview::message_header) + 41, "unexpected sizeof net_order_imbalance_indicator_message");

#pragma pack(pop)
}
