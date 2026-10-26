#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/TrdType.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/MultiLegReportingType.hpp"
#include "../types/MultiLegPriceModel.hpp"
#include "../types/Pad6.hpp"
#include "../types/NonDisclosedTradeVolume.hpp"
#include "../types/TransBkdTime.hpp"
#include "../types/NumberOfBuySides.hpp"
#include "../types/NumberOfSellSides.hpp"
#include "../types/Pad4.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Tes Trade Report
struct tes_trade_report {

    struct fields_type {
        fbe_eobi::security_id security_id;
        fbe_eobi::transact_time transact_time;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::last_px last_px;
        fbe_eobi::trd_match_id trd_match_id;
        fbe_eobi::trd_type trd_type;
        fbe_eobi::trade_condition trade_condition;
        fbe_eobi::multi_leg_reporting_type multi_leg_reporting_type;
        fbe_eobi::multi_leg_price_model multi_leg_price_model;
        fbe_eobi::pad6 pad6;
        fbe_eobi::non_disclosed_trade_volume non_disclosed_trade_volume;
        fbe_eobi::trans_bkd_time trans_bkd_time;
        fbe_eobi::number_of_buy_sides number_of_buy_sides;
        fbe_eobi::number_of_sell_sides number_of_sell_sides;
        fbe_eobi::pad4 pad4;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::tes_trade_report, {}};

    fields_type fields;

    // parse method
    static tes_trade_report* parse(std::byte* buffer) {
        return reinterpret_cast<tes_trade_report*>(buffer);
    }

    // parse method const
    static const tes_trade_report* parse(const std::byte* buffer) {
        return reinterpret_cast<const tes_trade_report*>(buffer);
    }

};

// layout verification
static_assert(offsetof(tes_trade_report::fields_type, security_id) == 0, "unexpected offset of tes_trade_report::fields_type::security_id");
static_assert(offsetof(tes_trade_report::fields_type, transact_time) == 8, "unexpected offset of tes_trade_report::fields_type::transact_time");
static_assert(offsetof(tes_trade_report::fields_type, last_qty) == 16, "unexpected offset of tes_trade_report::fields_type::last_qty");
static_assert(offsetof(tes_trade_report::fields_type, last_px) == 24, "unexpected offset of tes_trade_report::fields_type::last_px");
static_assert(offsetof(tes_trade_report::fields_type, trd_match_id) == 32, "unexpected offset of tes_trade_report::fields_type::trd_match_id");
static_assert(offsetof(tes_trade_report::fields_type, trd_type) == 36, "unexpected offset of tes_trade_report::fields_type::trd_type");
static_assert(offsetof(tes_trade_report::fields_type, trade_condition) == 38, "unexpected offset of tes_trade_report::fields_type::trade_condition");
static_assert(offsetof(tes_trade_report::fields_type, multi_leg_reporting_type) == 40, "unexpected offset of tes_trade_report::fields_type::multi_leg_reporting_type");
static_assert(offsetof(tes_trade_report::fields_type, multi_leg_price_model) == 41, "unexpected offset of tes_trade_report::fields_type::multi_leg_price_model");
static_assert(offsetof(tes_trade_report::fields_type, pad6) == 42, "unexpected offset of tes_trade_report::fields_type::pad6");
static_assert(offsetof(tes_trade_report::fields_type, non_disclosed_trade_volume) == 48, "unexpected offset of tes_trade_report::fields_type::non_disclosed_trade_volume");
static_assert(offsetof(tes_trade_report::fields_type, trans_bkd_time) == 56, "unexpected offset of tes_trade_report::fields_type::trans_bkd_time");
static_assert(offsetof(tes_trade_report::fields_type, number_of_buy_sides) == 64, "unexpected offset of tes_trade_report::fields_type::number_of_buy_sides");
static_assert(offsetof(tes_trade_report::fields_type, number_of_sell_sides) == 66, "unexpected offset of tes_trade_report::fields_type::number_of_sell_sides");
static_assert(offsetof(tes_trade_report::fields_type, pad4) == 68, "unexpected offset of tes_trade_report::fields_type::pad4");
static_assert(sizeof(tes_trade_report::fields_type) == 72, "unexpected sizeof tes_trade_report::fields_type");
static_assert(sizeof(tes_trade_report) == sizeof(fbe_eobi::message_header_comp) + 72, "unexpected sizeof tes_trade_report");

#pragma pack(pop)
}
