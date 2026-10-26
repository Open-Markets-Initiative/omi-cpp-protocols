#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/Side.hpp"
#include "../types/OrdType.hpp"
#include "../types/AlgorithmicTradeIndicator.hpp"
#include "../types/HhiIndicator.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/Price.hpp"
#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Partial Order Execution
struct partial_order_execution {

    struct fields_type {
        fbe_eobi::side side;
        fbe_eobi::ord_type ord_type;
        fbe_eobi::algorithmic_trade_indicator algorithmic_trade_indicator;
        fbe_eobi::hhi_indicator hhi_indicator;
        fbe_eobi::trd_match_id trd_match_id;
        fbe_eobi::price price;
        fbe_eobi::trd_reg_ts_time_priority trd_reg_ts_time_priority;
        fbe_eobi::security_id security_id;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::last_px last_px;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::partial_order_execution, {}};

    fields_type fields;

    // parse method
    static partial_order_execution* parse(std::byte* buffer) {
        return reinterpret_cast<partial_order_execution*>(buffer);
    }

    // parse method const
    static const partial_order_execution* parse(const std::byte* buffer) {
        return reinterpret_cast<const partial_order_execution*>(buffer);
    }

};

// layout verification
static_assert(offsetof(partial_order_execution::fields_type, side) == 0, "unexpected offset of partial_order_execution::fields_type::side");
static_assert(offsetof(partial_order_execution::fields_type, ord_type) == 1, "unexpected offset of partial_order_execution::fields_type::ord_type");
static_assert(offsetof(partial_order_execution::fields_type, algorithmic_trade_indicator) == 2, "unexpected offset of partial_order_execution::fields_type::algorithmic_trade_indicator");
static_assert(offsetof(partial_order_execution::fields_type, hhi_indicator) == 3, "unexpected offset of partial_order_execution::fields_type::hhi_indicator");
static_assert(offsetof(partial_order_execution::fields_type, trd_match_id) == 4, "unexpected offset of partial_order_execution::fields_type::trd_match_id");
static_assert(offsetof(partial_order_execution::fields_type, price) == 8, "unexpected offset of partial_order_execution::fields_type::price");
static_assert(offsetof(partial_order_execution::fields_type, trd_reg_ts_time_priority) == 16, "unexpected offset of partial_order_execution::fields_type::trd_reg_ts_time_priority");
static_assert(offsetof(partial_order_execution::fields_type, security_id) == 24, "unexpected offset of partial_order_execution::fields_type::security_id");
static_assert(offsetof(partial_order_execution::fields_type, last_qty) == 32, "unexpected offset of partial_order_execution::fields_type::last_qty");
static_assert(offsetof(partial_order_execution::fields_type, last_px) == 40, "unexpected offset of partial_order_execution::fields_type::last_px");
static_assert(sizeof(partial_order_execution::fields_type) == 48, "unexpected sizeof partial_order_execution::fields_type");
static_assert(sizeof(partial_order_execution) == sizeof(fbe_eobi::message_header_comp) + 48, "unexpected sizeof partial_order_execution");

#pragma pack(pop)
}
