#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/MatchType.hpp"
#include "../types/MatchSubType.hpp"
#include "../types/AlgorithmicTradeIndicator.hpp"
#include "../types/Pad1.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Pad6.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v13_0;

#pragma pack(push, 1)

// Trade Report
struct trade_report {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::last_px last_px;
        fbe_eobi::trd_match_id trd_match_id;
        fbe_eobi::match_type match_type;
        fbe_eobi::match_sub_type match_sub_type;
        fbe_eobi::algorithmic_trade_indicator algorithmic_trade_indicator;
        fbe_eobi::pad1 pad1;
        fbe_eobi::trade_condition trade_condition;
        fbe_eobi::pad6 pad6;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::trade_report, {}};

    fields_type fields;

    // parse method
    static trade_report* parse(std::byte* buffer) {
        return reinterpret_cast<trade_report*>(buffer);
    }

    // parse method const
    static const trade_report* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_report*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_report::fields_type, security_id) == 0, "unexpected offset of trade_report::fields_type::security_id");
static_assert(offsetof(trade_report::fields_type, transact_time) == 8, "unexpected offset of trade_report::fields_type::transact_time");
static_assert(offsetof(trade_report::fields_type, last_qty) == 16, "unexpected offset of trade_report::fields_type::last_qty");
static_assert(offsetof(trade_report::fields_type, last_px) == 24, "unexpected offset of trade_report::fields_type::last_px");
static_assert(offsetof(trade_report::fields_type, trd_match_id) == 32, "unexpected offset of trade_report::fields_type::trd_match_id");
static_assert(offsetof(trade_report::fields_type, match_type) == 36, "unexpected offset of trade_report::fields_type::match_type");
static_assert(offsetof(trade_report::fields_type, match_sub_type) == 37, "unexpected offset of trade_report::fields_type::match_sub_type");
static_assert(offsetof(trade_report::fields_type, algorithmic_trade_indicator) == 38, "unexpected offset of trade_report::fields_type::algorithmic_trade_indicator");
static_assert(offsetof(trade_report::fields_type, pad1) == 39, "unexpected offset of trade_report::fields_type::pad1");
static_assert(offsetof(trade_report::fields_type, trade_condition) == 40, "unexpected offset of trade_report::fields_type::trade_condition");
static_assert(offsetof(trade_report::fields_type, pad6) == 42, "unexpected offset of trade_report::fields_type::pad6");
static_assert(sizeof(trade_report::fields_type) == 48, "unexpected sizeof trade_report::fields_type");
static_assert(sizeof(trade_report) == sizeof(fbe_eobi::message_header_comp) + 48, "unexpected sizeof trade_report");

#pragma pack(pop)
}
