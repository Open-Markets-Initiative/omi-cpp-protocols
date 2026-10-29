#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TransactTime.hpp"
#include "../types/PrevDisplayQty.hpp"
#include "../types/Pad4.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

// Order Modify Same Prio
struct order_modify_same_prio {

    struct fields_type {
        fbe_eobi::trd_reg_ts_time_in trd_reg_ts_time_in;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::prev_display_qty prev_display_qty;
        fbe_eobi::pad4 pad4;
        fbe_eobi::security_id security_id;
        fbe_eobi::order_details_comp order_details_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::order_modify_same_prio, {}};

    fields_type fields;

    // parse method
    static order_modify_same_prio* parse(std::byte* buffer) {
        return reinterpret_cast<order_modify_same_prio*>(buffer);
    }

    // parse method const
    static const order_modify_same_prio* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_modify_same_prio*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_modify_same_prio::fields_type, trd_reg_ts_time_in) == 0, "unexpected offset of order_modify_same_prio::fields_type::trd_reg_ts_time_in");
static_assert(offsetof(order_modify_same_prio::fields_type, transact_time) == 8, "unexpected offset of order_modify_same_prio::fields_type::transact_time");
static_assert(offsetof(order_modify_same_prio::fields_type, prev_display_qty) == 16, "unexpected offset of order_modify_same_prio::fields_type::prev_display_qty");
static_assert(offsetof(order_modify_same_prio::fields_type, pad4) == 20, "unexpected offset of order_modify_same_prio::fields_type::pad4");
static_assert(offsetof(order_modify_same_prio::fields_type, security_id) == 24, "unexpected offset of order_modify_same_prio::fields_type::security_id");
static_assert(offsetof(order_modify_same_prio::fields_type, order_details_comp) == 32, "unexpected offset of order_modify_same_prio::fields_type::order_details_comp");
static_assert(sizeof(order_modify_same_prio::fields_type) == 56, "unexpected sizeof order_modify_same_prio::fields_type");
static_assert(sizeof(order_modify_same_prio) == sizeof(fbe_eobi::message_header_comp) + 56, "unexpected sizeof order_modify_same_prio");

#pragma pack(pop)
}
