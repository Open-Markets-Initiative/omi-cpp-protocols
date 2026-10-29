#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TrdRegTsPrevTimePriority.hpp"
#include "../types/PrevPrice.hpp"
#include "../types/PrevDisplayQty.hpp"
#include "../types/Pad4.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

// Order Modify
struct order_modify {

    struct fields_type {
        fbe_eobi::trd_reg_ts_time_in trd_reg_ts_time_in;
        fbe_eobi::trd_reg_ts_prev_time_priority trd_reg_ts_prev_time_priority;
        fbe_eobi::prev_price prev_price;
        fbe_eobi::prev_display_qty prev_display_qty;
        fbe_eobi::pad4 pad4;
        fbe_eobi::security_id security_id;
        fbe_eobi::order_details_comp order_details_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::order_modify, {}};

    fields_type fields;

    // parse method
    static order_modify* parse(std::byte* buffer) {
        return reinterpret_cast<order_modify*>(buffer);
    }

    // parse method const
    static const order_modify* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_modify*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_modify::fields_type, trd_reg_ts_time_in) == 0, "unexpected offset of order_modify::fields_type::trd_reg_ts_time_in");
static_assert(offsetof(order_modify::fields_type, trd_reg_ts_prev_time_priority) == 8, "unexpected offset of order_modify::fields_type::trd_reg_ts_prev_time_priority");
static_assert(offsetof(order_modify::fields_type, prev_price) == 16, "unexpected offset of order_modify::fields_type::prev_price");
static_assert(offsetof(order_modify::fields_type, prev_display_qty) == 24, "unexpected offset of order_modify::fields_type::prev_display_qty");
static_assert(offsetof(order_modify::fields_type, pad4) == 28, "unexpected offset of order_modify::fields_type::pad4");
static_assert(offsetof(order_modify::fields_type, security_id) == 32, "unexpected offset of order_modify::fields_type::security_id");
static_assert(offsetof(order_modify::fields_type, order_details_comp) == 40, "unexpected offset of order_modify::fields_type::order_details_comp");
static_assert(sizeof(order_modify::fields_type) == 64, "unexpected sizeof order_modify::fields_type");
static_assert(sizeof(order_modify) == sizeof(fbe_eobi::message_header_comp) + 64, "unexpected sizeof order_modify");

#pragma pack(pop)
}
