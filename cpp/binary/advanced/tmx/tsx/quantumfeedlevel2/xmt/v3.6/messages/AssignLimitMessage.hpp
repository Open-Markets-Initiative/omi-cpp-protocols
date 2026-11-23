// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/AssignLimitMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/BusinessHeader.hpp"
#include "../types/Symbol.hpp"
#include "../types/CalculatedOpeningPrice.hpp"
#include "../types/OrderSide.hpp"
#include "../structs/CopLimit.hpp"
#include "../types/TradingSystemTimeStamp.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

#pragma pack(push, 1)

// Assign Limit Message
struct assign_limit_message {

    struct fields_type {
        xmt_quantumfeedlevel2::symbol symbol;
        xmt_quantumfeedlevel2::calculated_opening_price calculated_opening_price;
        xmt_quantumfeedlevel2::order_side order_side;
        xmt_quantumfeedlevel2::cop_limit cop_limit[15];
        xmt_quantumfeedlevel2::trading_system_time_stamp trading_system_time_stamp;
    };

    xmt_quantumfeedlevel2::business_header header = {{}, {}, {}, sequence_0(0), {}};

    fields_type fields;

    // parse method
    static assign_limit_message* parse(std::byte* buffer) {
        return reinterpret_cast<assign_limit_message*>(buffer);
    }

    // parse method const
    static const assign_limit_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const assign_limit_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(assign_limit_message::fields_type, symbol) == 0, "unexpected offset of assign_limit_message::fields_type::symbol");
static_assert(offsetof(assign_limit_message::fields_type, calculated_opening_price) == 12, "unexpected offset of assign_limit_message::fields_type::calculated_opening_price");
static_assert(offsetof(assign_limit_message::fields_type, order_side) == 20, "unexpected offset of assign_limit_message::fields_type::order_side");
static_assert(offsetof(assign_limit_message::fields_type, cop_limit) == 21, "unexpected offset of assign_limit_message::fields_type::cop_limit");
static_assert(offsetof(assign_limit_message::fields_type, trading_system_time_stamp) == 291, "unexpected offset of assign_limit_message::fields_type::trading_system_time_stamp");
static_assert(sizeof(assign_limit_message::fields_type) == 299, "unexpected sizeof assign_limit_message::fields_type");
static_assert(sizeof(assign_limit_message) == sizeof(xmt_quantumfeedlevel2::business_header) + 299, "unexpected sizeof assign_limit_message");

#pragma pack(pop)
}
