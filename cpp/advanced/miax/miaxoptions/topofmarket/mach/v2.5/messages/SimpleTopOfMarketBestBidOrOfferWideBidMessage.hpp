#pragma once

#include <cstddef>
#include "../types/Nanoseconds.hpp"
#include "../types/ProductId.hpp"
#include "../types/MbboPriceLong.hpp"
#include "../types/MbboSizeLong.hpp"
#include "../types/MbboPriorityCustomerSizeLong.hpp"
#include "../types/MbboCondition.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/PacketLength.hpp"
#include "../types/PacketType.hpp"
#include "../types/SessionNumber.hpp"
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

    mach_topofmarket::sequence_number sequence_number;
    // Transport framing: message size precedes the SBE header on the wire
    mach_topofmarket::packet_length packet_length;
    mach_topofmarket::packet_type packet_type = mach_topofmarket::packet_type::enum_type::application_message;
    mach_topofmarket::session_number session_number;
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
static_assert(sizeof(simple_top_of_market_best_bid_or_offer_wide_bid_message) == sizeof(mach_topofmarket::sequence_number) + sizeof(mach_topofmarket::packet_length) + sizeof(mach_topofmarket::packet_type) + sizeof(mach_topofmarket::session_number) + sizeof(mach_topofmarket::message_type) + 21, "unexpected sizeof simple_top_of_market_best_bid_or_offer_wide_bid_message");

#pragma pack(pop)
}
