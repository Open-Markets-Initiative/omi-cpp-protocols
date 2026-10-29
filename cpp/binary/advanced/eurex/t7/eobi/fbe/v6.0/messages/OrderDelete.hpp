#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

// Order Delete
struct order_delete {

    struct fields_type {
        fbe_eobi::trd_reg_ts_time_in trd_reg_ts_time_in;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::order_details_comp order_details_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::order_delete, {}};

    fields_type fields;

    // parse method
    static order_delete* parse(std::byte* buffer) {
        return reinterpret_cast<order_delete*>(buffer);
    }

    // parse method const
    static const order_delete* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_delete*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_delete::fields_type, trd_reg_ts_time_in) == 0, "unexpected offset of order_delete::fields_type::trd_reg_ts_time_in");
static_assert(offsetof(order_delete::fields_type, transact_time) == 8, "unexpected offset of order_delete::fields_type::transact_time");
static_assert(offsetof(order_delete::fields_type, security_id) == 16, "unexpected offset of order_delete::fields_type::security_id");
static_assert(offsetof(order_delete::fields_type, order_details_comp) == 24, "unexpected offset of order_delete::fields_type::order_details_comp");
static_assert(sizeof(order_delete::fields_type) == 48, "unexpected sizeof order_delete::fields_type");
static_assert(sizeof(order_delete) == sizeof(fbe_eobi::message_header_comp) + 48, "unexpected sizeof order_delete");

#pragma pack(pop)
}
