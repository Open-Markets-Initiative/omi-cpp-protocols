#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AggressorTime.hpp"
#include "../types/RequestTime.hpp"
#include "../types/ExecId.hpp"
#include "../types/LastQty.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Pad2.hpp"
#include "../types/LastPx.hpp"
#include "../types/RestingHiddenQty.hpp"
#include "../types/RestingCxlQty.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

// Execution Summary
struct execution_summary {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::aggressor_time aggressor_time;
        fbe_eobi::request_time request_time;
        fbe_eobi::exec_id exec_id;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::aggressor_side aggressor_side;
        fbe_eobi::trade_condition trade_condition;
        fbe_eobi::pad2 pad2;
        fbe_eobi::last_px last_px;
        fbe_eobi::resting_hidden_qty resting_hidden_qty;
        fbe_eobi::resting_cxl_qty resting_cxl_qty;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::execution_summary, {}};

    fields_type fields;

    // parse method
    static execution_summary* parse(std::byte* buffer) {
        return reinterpret_cast<execution_summary*>(buffer);
    }

    // parse method const
    static const execution_summary* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_summary*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_summary::fields_type, security_id) == 0, "unexpected offset of execution_summary::fields_type::security_id");
static_assert(offsetof(execution_summary::fields_type, aggressor_time) == 8, "unexpected offset of execution_summary::fields_type::aggressor_time");
static_assert(offsetof(execution_summary::fields_type, request_time) == 16, "unexpected offset of execution_summary::fields_type::request_time");
static_assert(offsetof(execution_summary::fields_type, exec_id) == 24, "unexpected offset of execution_summary::fields_type::exec_id");
static_assert(offsetof(execution_summary::fields_type, last_qty) == 32, "unexpected offset of execution_summary::fields_type::last_qty");
static_assert(offsetof(execution_summary::fields_type, aggressor_side) == 36, "unexpected offset of execution_summary::fields_type::aggressor_side");
static_assert(offsetof(execution_summary::fields_type, trade_condition) == 37, "unexpected offset of execution_summary::fields_type::trade_condition");
static_assert(offsetof(execution_summary::fields_type, pad2) == 38, "unexpected offset of execution_summary::fields_type::pad2");
static_assert(offsetof(execution_summary::fields_type, last_px) == 40, "unexpected offset of execution_summary::fields_type::last_px");
static_assert(offsetof(execution_summary::fields_type, resting_hidden_qty) == 48, "unexpected offset of execution_summary::fields_type::resting_hidden_qty");
static_assert(offsetof(execution_summary::fields_type, resting_cxl_qty) == 52, "unexpected offset of execution_summary::fields_type::resting_cxl_qty");
static_assert(sizeof(execution_summary::fields_type) == 56, "unexpected sizeof execution_summary::fields_type");
static_assert(sizeof(execution_summary) == sizeof(fbe_eobi::message_header_comp) + 56, "unexpected sizeof execution_summary");

#pragma pack(pop)
}
