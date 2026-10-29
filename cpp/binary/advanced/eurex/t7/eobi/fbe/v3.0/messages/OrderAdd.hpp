#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TrdRegTsTimeIn.hpp"
#include "../types/SecurityId.hpp"
#include "../structs/OrderDetailsComp.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Order Add
struct order_add {

    struct fields_type {
        fbe_eobi::trd_reg_ts_time_in trd_reg_ts_time_in;
        fbe_eobi::security_id security_id;
        fbe_eobi::order_details_comp order_details_comp;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::order_add, {}};

    fields_type fields;

    // parse method
    static order_add* parse(std::byte* buffer) {
        return reinterpret_cast<order_add*>(buffer);
    }

    // parse method const
    static const order_add* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_add*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_add::fields_type, trd_reg_ts_time_in) == 0, "unexpected offset of order_add::fields_type::trd_reg_ts_time_in");
static_assert(offsetof(order_add::fields_type, security_id) == 8, "unexpected offset of order_add::fields_type::security_id");
static_assert(offsetof(order_add::fields_type, order_details_comp) == 16, "unexpected offset of order_add::fields_type::order_details_comp");
static_assert(sizeof(order_add::fields_type) == 40, "unexpected sizeof order_add::fields_type");
static_assert(sizeof(order_add) == sizeof(fbe_eobi::message_header_comp) + 40, "unexpected sizeof order_add");

#pragma pack(pop)
}
