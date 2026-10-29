#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Side.hpp"
#include "../types/Pad7.hpp"
#include "../types/Price.hpp"
#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/Pad4.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Full Order Execution Message
struct full_order_execution_message {

    struct fields_type {
        fbe_eobi::side side;
        fbe_eobi::pad_7 pad_7;
        fbe_eobi::price price;
        fbe_eobi::trd_reg_ts_time_priority trd_reg_ts_time_priority;
        fbe_eobi::security_id security_id;
        fbe_eobi::trd_match_id trd_match_id;
        fbe_eobi::pad_4 pad_4;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::last_px last_px;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::full_order_execution_message, {}};

    fields_type fields;

    // parse method
    static full_order_execution_message* parse(std::byte* buffer) {
        return reinterpret_cast<full_order_execution_message*>(buffer);
    }

    // parse method const
    static const full_order_execution_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const full_order_execution_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(full_order_execution_message::fields_type, side) == 0, "unexpected offset of full_order_execution_message::fields_type::side");
static_assert(offsetof(full_order_execution_message::fields_type, pad_7) == 1, "unexpected offset of full_order_execution_message::fields_type::pad_7");
static_assert(offsetof(full_order_execution_message::fields_type, price) == 8, "unexpected offset of full_order_execution_message::fields_type::price");
static_assert(offsetof(full_order_execution_message::fields_type, trd_reg_ts_time_priority) == 16, "unexpected offset of full_order_execution_message::fields_type::trd_reg_ts_time_priority");
static_assert(offsetof(full_order_execution_message::fields_type, security_id) == 24, "unexpected offset of full_order_execution_message::fields_type::security_id");
static_assert(offsetof(full_order_execution_message::fields_type, trd_match_id) == 32, "unexpected offset of full_order_execution_message::fields_type::trd_match_id");
static_assert(offsetof(full_order_execution_message::fields_type, pad_4) == 36, "unexpected offset of full_order_execution_message::fields_type::pad_4");
static_assert(offsetof(full_order_execution_message::fields_type, last_qty) == 40, "unexpected offset of full_order_execution_message::fields_type::last_qty");
static_assert(offsetof(full_order_execution_message::fields_type, last_px) == 48, "unexpected offset of full_order_execution_message::fields_type::last_px");
static_assert(sizeof(full_order_execution_message::fields_type) == 56, "unexpected sizeof full_order_execution_message::fields_type");
static_assert(sizeof(full_order_execution_message) == sizeof(fbe_eobi::message_header) + 56, "unexpected sizeof full_order_execution_message");

#pragma pack(pop)
}
