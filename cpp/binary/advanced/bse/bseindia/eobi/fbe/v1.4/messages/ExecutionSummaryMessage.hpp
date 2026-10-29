#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AggressorTimestamp.hpp"
#include "../types/ExecId.hpp"
#include "../types/LastQty.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Pad6.hpp"
#include "../types/LastPx.hpp"
#include "../types/RestingHiddenQty.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Execution Summary Message
struct execution_summary_message {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::aggressor_timestamp aggressor_timestamp;
        fbe_eobi::exec_id exec_id;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::aggressor_side aggressor_side;
        fbe_eobi::trade_condition trade_condition;
        fbe_eobi::pad_6 pad_6;
        fbe_eobi::last_px last_px;
        fbe_eobi::resting_hidden_qty resting_hidden_qty;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::execution_summary_message, {}};

    fields_type fields;

    // parse method
    static execution_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_summary_message*>(buffer);
    }

    // parse method const
    static const execution_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_summary_message::fields_type, security_id) == 0, "unexpected offset of execution_summary_message::fields_type::security_id");
static_assert(offsetof(execution_summary_message::fields_type, aggressor_timestamp) == 8, "unexpected offset of execution_summary_message::fields_type::aggressor_timestamp");
static_assert(offsetof(execution_summary_message::fields_type, exec_id) == 16, "unexpected offset of execution_summary_message::fields_type::exec_id");
static_assert(offsetof(execution_summary_message::fields_type, last_qty) == 24, "unexpected offset of execution_summary_message::fields_type::last_qty");
static_assert(offsetof(execution_summary_message::fields_type, aggressor_side) == 32, "unexpected offset of execution_summary_message::fields_type::aggressor_side");
static_assert(offsetof(execution_summary_message::fields_type, trade_condition) == 33, "unexpected offset of execution_summary_message::fields_type::trade_condition");
static_assert(offsetof(execution_summary_message::fields_type, pad_6) == 34, "unexpected offset of execution_summary_message::fields_type::pad_6");
static_assert(offsetof(execution_summary_message::fields_type, last_px) == 40, "unexpected offset of execution_summary_message::fields_type::last_px");
static_assert(offsetof(execution_summary_message::fields_type, resting_hidden_qty) == 48, "unexpected offset of execution_summary_message::fields_type::resting_hidden_qty");
static_assert(sizeof(execution_summary_message::fields_type) == 56, "unexpected sizeof execution_summary_message::fields_type");
static_assert(sizeof(execution_summary_message) == sizeof(fbe_eobi::message_header) + 56, "unexpected sizeof execution_summary_message");

#pragma pack(pop)
}
