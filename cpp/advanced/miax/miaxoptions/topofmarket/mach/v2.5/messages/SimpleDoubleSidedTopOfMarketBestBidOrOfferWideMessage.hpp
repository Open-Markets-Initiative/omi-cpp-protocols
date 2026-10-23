#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/BidPriceLong.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/BidPriorityCustomerSizeLong.hpp"
#include "../types/BidCondition.hpp"
#include "../types/OfferPriceLong.hpp"
#include "../types/OfferSizeLong.hpp"
#include "../types/OfferPriorityCustomerSizeLong.hpp"
#include "../types/OfferCondition.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"
#include "../types/MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

#pragma pack(push, 1)

// Simple Double Sided Top Of Market Best Bid Or Offer Wide Message
struct simple_double_sided_top_of_market_best_bid_or_offer_wide_message {

    struct fields_type {
        mach_topofmarket::nanoseconds nanoseconds;
        mach_topofmarket::product_id product_id;
        mach_topofmarket::bid_price_long bid_price_long;
        mach_topofmarket::bid_size_long bid_size_long;
        mach_topofmarket::bid_priority_customer_size_long bid_priority_customer_size_long;
        mach_topofmarket::bid_condition bid_condition;
        mach_topofmarket::offer_price_long offer_price_long;
        mach_topofmarket::offer_size_long offer_size_long;
        mach_topofmarket::offer_priority_customer_size_long offer_priority_customer_size_long;
        mach_topofmarket::offer_condition offer_condition;
    };

    mach_topofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_topofmarket::packet_length packet_length;
    mach_topofmarket::packet_type packet_type = mach_topofmarket::packet_type::enum_type::application_message;
    mach_topofmarket::session_number session_number;
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::simple_double_sided_top_of_market_best_bid_or_offer_wide_message;

    fields_type fields;

    // parse method
    static simple_double_sided_top_of_market_best_bid_or_offer_wide_message* parse(std::byte* buffer) {
        return reinterpret_cast<simple_double_sided_top_of_market_best_bid_or_offer_wide_message*>(buffer);
    }

    // parse method const
    static const simple_double_sided_top_of_market_best_bid_or_offer_wide_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const simple_double_sided_top_of_market_best_bid_or_offer_wide_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, nanoseconds) == 0, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::nanoseconds");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, product_id) == 4, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::product_id");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, bid_price_long) == 8, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::bid_price_long");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, bid_size_long) == 12, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::bid_size_long");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, bid_priority_customer_size_long) == 16, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::bid_priority_customer_size_long");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, bid_condition) == 20, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::bid_condition");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, offer_price_long) == 21, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::offer_price_long");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, offer_size_long) == 25, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::offer_size_long");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, offer_priority_customer_size_long) == 29, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::offer_priority_customer_size_long");
static_assert(offsetof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type, offer_condition) == 33, "unexpected offset of simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type::offer_condition");
static_assert(sizeof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type) == 34, "unexpected sizeof simple_double_sided_top_of_market_best_bid_or_offer_wide_message::fields_type");
static_assert(sizeof(simple_double_sided_top_of_market_best_bid_or_offer_wide_message) == sizeof(mach_topofmarket::sequence_number) + sizeof(mach_topofmarket::packet_length) + sizeof(mach_topofmarket::packet_type) + sizeof(mach_topofmarket::session_number) + sizeof(mach_topofmarket::message_type) + 34, "unexpected sizeof simple_double_sided_top_of_market_best_bid_or_offer_wide_message");

#pragma pack(pop)
}
