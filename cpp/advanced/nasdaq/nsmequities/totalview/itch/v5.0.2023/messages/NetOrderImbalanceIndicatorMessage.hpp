#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/PairedShares.hpp"
#include "../types/ImbalanceShares.hpp"
#include "../types/ImbalanceDirection.hpp"
#include "../types/Stock.hpp"
#include "../types/FarPrice.hpp"
#include "../types/NearPrice.hpp"
#include "../types/CurrentReferencePrice.hpp"
#include "../types/CrossType.hpp"
#include "../types/PriceVariationIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Net Order Imbalance Indicator Message
struct net_order_imbalance_indicator_message {

    struct fields_type {
        itch_totalview::stock_locate stock_locate;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::timestamp timestamp;
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

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 2), message_type::enum_type::net_order_imbalance_indicator_message};

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
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, stock_locate) == 0, "unexpected offset of net_order_imbalance_indicator_message::fields_type::stock_locate");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, tracking_number) == 2, "unexpected offset of net_order_imbalance_indicator_message::fields_type::tracking_number");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, timestamp) == 4, "unexpected offset of net_order_imbalance_indicator_message::fields_type::timestamp");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, paired_shares) == 10, "unexpected offset of net_order_imbalance_indicator_message::fields_type::paired_shares");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, imbalance_shares) == 18, "unexpected offset of net_order_imbalance_indicator_message::fields_type::imbalance_shares");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, imbalance_direction) == 26, "unexpected offset of net_order_imbalance_indicator_message::fields_type::imbalance_direction");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, stock) == 27, "unexpected offset of net_order_imbalance_indicator_message::fields_type::stock");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, far_price) == 35, "unexpected offset of net_order_imbalance_indicator_message::fields_type::far_price");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, near_price) == 39, "unexpected offset of net_order_imbalance_indicator_message::fields_type::near_price");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, current_reference_price) == 43, "unexpected offset of net_order_imbalance_indicator_message::fields_type::current_reference_price");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, cross_type) == 47, "unexpected offset of net_order_imbalance_indicator_message::fields_type::cross_type");
static_assert(offsetof(net_order_imbalance_indicator_message::fields_type, price_variation_indicator) == 48, "unexpected offset of net_order_imbalance_indicator_message::fields_type::price_variation_indicator");
static_assert(sizeof(net_order_imbalance_indicator_message::fields_type) == 49, "unexpected sizeof net_order_imbalance_indicator_message::fields_type");
static_assert(sizeof(net_order_imbalance_indicator_message) == sizeof(message_header) + 49, "unexpected sizeof net_order_imbalance_indicator_message");

#pragma pack(pop)
}
