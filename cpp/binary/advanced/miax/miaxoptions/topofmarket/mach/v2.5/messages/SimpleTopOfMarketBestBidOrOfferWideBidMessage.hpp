// Miax.MiaxOptions.TopOfMarket.Mach.v2.5: messages/SimpleTopOfMarketBestBidOrOfferWideBidMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/MbboPriceLong.hpp"
#include "../types/MbboSizeLong.hpp"
#include "../types/MbboPriorityCustomerSizeLong.hpp"
#include "../types/MbboCondition.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// Simple Top Of Market Best Bid Or Offer Wide Bid Message
struct simple_top_of_market_best_bid_or_offer_wide_bid_message {

    struct fields_type {
        mach_topofmarket::nanoseconds nanoseconds;
        mach_topofmarket::product_id product_id;
        mach_topofmarket::mbbo_price_long mbbo_price_long;
        mach_topofmarket::mbbo_size_long mbbo_size_long;
        mach_topofmarket::mbbo_priority_customer_size_long mbbo_priority_customer_size_long;
        mach_topofmarket::mbbo_condition mbbo_condition;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::simple_top_of_market_best_bid_or_offer_wide_bid_message;

    fields_type fields;

    // parse method
    static simple_top_of_market_best_bid_or_offer_wide_bid_message* parse(std::byte* buffer) {
        return reinterpret_cast<simple_top_of_market_best_bid_or_offer_wide_bid_message*>(buffer);
    }

    // parse method const
    static const simple_top_of_market_best_bid_or_offer_wide_bid_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const simple_top_of_market_best_bid_or_offer_wide_bid_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type, nanoseconds) == 0, "unexpected offset of simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type::nanoseconds");
static_assert(offsetof(simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type, product_id) == 4, "unexpected offset of simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type::product_id");
static_assert(offsetof(simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type, mbbo_price_long) == 8, "unexpected offset of simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type::mbbo_price_long");
static_assert(offsetof(simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type, mbbo_size_long) == 12, "unexpected offset of simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type::mbbo_size_long");
static_assert(offsetof(simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type, mbbo_priority_customer_size_long) == 16, "unexpected offset of simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type::mbbo_priority_customer_size_long");
static_assert(offsetof(simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type, mbbo_condition) == 20, "unexpected offset of simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type::mbbo_condition");
static_assert(sizeof(simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type) == 21, "unexpected sizeof simple_top_of_market_best_bid_or_offer_wide_bid_message::fields_type");
static_assert(sizeof(simple_top_of_market_best_bid_or_offer_wide_bid_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 21, "unexpected sizeof simple_top_of_market_best_bid_or_offer_wide_bid_message");

#pragma pack(pop)
}
