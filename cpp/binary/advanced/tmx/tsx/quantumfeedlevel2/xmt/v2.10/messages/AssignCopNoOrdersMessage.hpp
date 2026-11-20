// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/AssignCopNoOrdersMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/CalculatedOpeningPrice.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v2_10;

#pragma pack(push, 1)

// Assign Cop No Orders Message
struct assign_cop_no_orders_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::calculated_opening_price calculated_opening_price;
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static assign_cop_no_orders_message* parse(std::byte* buffer) {
        return reinterpret_cast<assign_cop_no_orders_message*>(buffer);
    }

    // parse method const
    static const assign_cop_no_orders_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const assign_cop_no_orders_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(assign_cop_no_orders_message::fields_type, symbol) == 0, "unexpected offset of assign_cop_no_orders_message::fields_type::symbol");
static_assert(offsetof(assign_cop_no_orders_message::fields_type, calculated_opening_price) == 9, "unexpected offset of assign_cop_no_orders_message::fields_type::calculated_opening_price");
static_assert(offsetof(assign_cop_no_orders_message::fields_type, trading_system_time_stamp) == 17, "unexpected offset of assign_cop_no_orders_message::fields_type::trading_system_time_stamp");
static_assert(sizeof(assign_cop_no_orders_message::fields_type) == 25, "unexpected sizeof assign_cop_no_orders_message::fields_type");
static_assert(sizeof(assign_cop_no_orders_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 25, "unexpected sizeof assign_cop_no_orders_message");

#pragma pack(pop)
}
