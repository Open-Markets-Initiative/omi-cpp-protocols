#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TrdRegTsPrevTimePriority.hpp"
#include "../types/PrevPrice.hpp"
#include "../types/PrevDisplayQty.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetails.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Order Modify Message
struct order_modify_message {

    struct fields_type {
        fbe_eobi::trd_reg_ts_time_in trd_reg_ts_time_in;
        fbe_eobi::trd_reg_ts_prev_time_priority trd_reg_ts_prev_time_priority;
        fbe_eobi::prev_price prev_price;
        fbe_eobi::prev_display_qty prev_display_qty;
        fbe_eobi::security_id security_id;
        fbe_eobi::order_details order_details;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::order_modify_message, {}};

    fields_type fields;

    // parse method
    static order_modify_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_modify_message*>(buffer);
    }

    // parse method const
    static const order_modify_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_modify_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_modify_message::fields_type, trd_reg_ts_time_in) == 0, "unexpected offset of order_modify_message::fields_type::trd_reg_ts_time_in");
static_assert(offsetof(order_modify_message::fields_type, trd_reg_ts_prev_time_priority) == 8, "unexpected offset of order_modify_message::fields_type::trd_reg_ts_prev_time_priority");
static_assert(offsetof(order_modify_message::fields_type, prev_price) == 16, "unexpected offset of order_modify_message::fields_type::prev_price");
static_assert(offsetof(order_modify_message::fields_type, prev_display_qty) == 24, "unexpected offset of order_modify_message::fields_type::prev_display_qty");
static_assert(offsetof(order_modify_message::fields_type, security_id) == 32, "unexpected offset of order_modify_message::fields_type::security_id");
static_assert(offsetof(order_modify_message::fields_type, order_details) == 40, "unexpected offset of order_modify_message::fields_type::order_details");
static_assert(sizeof(order_modify_message::fields_type) == 72, "unexpected sizeof order_modify_message::fields_type");
static_assert(sizeof(order_modify_message) == sizeof(fbe_eobi::message_header) + 72, "unexpected sizeof order_modify_message");

#pragma pack(pop)
}
