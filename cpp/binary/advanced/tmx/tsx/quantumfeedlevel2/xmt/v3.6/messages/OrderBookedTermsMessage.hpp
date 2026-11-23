// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/OrderBookedTermsMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/BrokerNumber.hpp"
#include "../types/OrderSide.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/NonResident.hpp"
#include "../types/SettlementTerms.hpp"
#include "../types/SettlementDate.hpp"
#include "../types/PriorityTimeStamp.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Order Booked Terms Message
struct order_booked_terms_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::broker_number broker_number;
        xmt_quantumfeedlevel2::order_side order_side;
        xmt_quantumfeedlevel2::order_id order_id;
        xmt_quantumfeedlevel2::price price;
        xmt_quantumfeedlevel2::volume volume;
        xmt_quantumfeedlevel2::non_resident non_resident;
        xmt_quantumfeedlevel2::settlement_terms settlement_terms;
        xmt_quantumfeedlevel2::settlement_date settlement_date;
        xmt_quantumfeedlevel2::priority_time_stamp priority_time_stamp;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static order_booked_terms_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_booked_terms_message*>(buffer);
    }

    // parse method const
    static const order_booked_terms_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_booked_terms_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_booked_terms_message::fields_type, symbol) == 0, "unexpected offset of order_booked_terms_message::fields_type::symbol");
static_assert(offsetof(order_booked_terms_message::fields_type, broker_number) == 12, "unexpected offset of order_booked_terms_message::fields_type::broker_number");
static_assert(offsetof(order_booked_terms_message::fields_type, order_side) == 14, "unexpected offset of order_booked_terms_message::fields_type::order_side");
static_assert(offsetof(order_booked_terms_message::fields_type, order_id) == 15, "unexpected offset of order_booked_terms_message::fields_type::order_id");
static_assert(offsetof(order_booked_terms_message::fields_type, price) == 23, "unexpected offset of order_booked_terms_message::fields_type::price");
static_assert(offsetof(order_booked_terms_message::fields_type, volume) == 31, "unexpected offset of order_booked_terms_message::fields_type::volume");
static_assert(offsetof(order_booked_terms_message::fields_type, non_resident) == 35, "unexpected offset of order_booked_terms_message::fields_type::non_resident");
static_assert(offsetof(order_booked_terms_message::fields_type, settlement_terms) == 36, "unexpected offset of order_booked_terms_message::fields_type::settlement_terms");
static_assert(offsetof(order_booked_terms_message::fields_type, settlement_date) == 37, "unexpected offset of order_booked_terms_message::fields_type::settlement_date");
static_assert(offsetof(order_booked_terms_message::fields_type, priority_time_stamp) == 41, "unexpected offset of order_booked_terms_message::fields_type::priority_time_stamp");
static_assert(offsetof(order_booked_terms_message::fields_type, trading_system_time_stamp) == 49, "unexpected offset of order_booked_terms_message::fields_type::trading_system_time_stamp");
static_assert(sizeof(order_booked_terms_message::fields_type) == 57, "unexpected sizeof order_booked_terms_message::fields_type");
static_assert(sizeof(order_booked_terms_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 57, "unexpected sizeof order_booked_terms_message");

#pragma pack(pop)
}
