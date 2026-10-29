#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/Side.hpp"
#include "../types/Pad7.hpp"
#include "../types/Price.hpp"
#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Full Order Execution
struct full_order_execution {

    struct fields_type {
        fbe_eobi::side side;
        fbe_eobi::pad7 pad7;
        fbe_eobi::price price;
        fbe_eobi::trd_reg_ts_time_priority trd_reg_ts_time_priority;
        fbe_eobi::security_id security_id;
        fbe_eobi::trd_match_id trd_match_id;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::last_px last_px;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::full_order_execution, {}};

    fields_type fields;

    // parse method
    static full_order_execution* parse(std::byte* buffer) {
        return reinterpret_cast<full_order_execution*>(buffer);
    }

    // parse method const
    static const full_order_execution* parse(const std::byte* buffer) {
        return reinterpret_cast<const full_order_execution*>(buffer);
    }

};

// layout verification
static_assert(offsetof(full_order_execution::fields_type, side) == 0, "unexpected offset of full_order_execution::fields_type::side");
static_assert(offsetof(full_order_execution::fields_type, pad7) == 1, "unexpected offset of full_order_execution::fields_type::pad7");
static_assert(offsetof(full_order_execution::fields_type, price) == 8, "unexpected offset of full_order_execution::fields_type::price");
static_assert(offsetof(full_order_execution::fields_type, trd_reg_ts_time_priority) == 16, "unexpected offset of full_order_execution::fields_type::trd_reg_ts_time_priority");
static_assert(offsetof(full_order_execution::fields_type, security_id) == 24, "unexpected offset of full_order_execution::fields_type::security_id");
static_assert(offsetof(full_order_execution::fields_type, trd_match_id) == 32, "unexpected offset of full_order_execution::fields_type::trd_match_id");
static_assert(offsetof(full_order_execution::fields_type, last_qty) == 36, "unexpected offset of full_order_execution::fields_type::last_qty");
static_assert(offsetof(full_order_execution::fields_type, last_px) == 40, "unexpected offset of full_order_execution::fields_type::last_px");
static_assert(sizeof(full_order_execution::fields_type) == 48, "unexpected sizeof full_order_execution::fields_type");
static_assert(sizeof(full_order_execution) == sizeof(fbe_eobi::message_header_comp) + 48, "unexpected sizeof full_order_execution");

#pragma pack(pop)
}
