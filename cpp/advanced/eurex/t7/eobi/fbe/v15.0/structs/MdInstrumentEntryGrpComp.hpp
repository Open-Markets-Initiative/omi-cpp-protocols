#pragma once

#include <cstddef>
#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/MdOriginType.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/TrdType.hpp"
#include "../types/MultiLegReportingType.hpp"
#include "../types/MultiLegPriceModel.hpp"
#include "../types/NonDisclosedTradeVolume.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

struct md_instrument_entry_grp_comp {

    fbe_eobi::md_entry_px md_entry_px;
    fbe_eobi::md_entry_size md_entry_size;
    fbe_eobi::md_origin_type md_origin_type;
    fbe_eobi::md_entry_type md_entry_type;
    fbe_eobi::trade_condition trade_condition;
    fbe_eobi::trd_type trd_type;
    fbe_eobi::multi_leg_reporting_type multi_leg_reporting_type;
    fbe_eobi::multi_leg_price_model multi_leg_price_model;
    fbe_eobi::non_disclosed_trade_volume non_disclosed_trade_volume;

    // parse method
    static md_instrument_entry_grp_comp* parse(std::byte* buffer) {
        return reinterpret_cast<md_instrument_entry_grp_comp*>(buffer);
    }

    // parse method const
    static const md_instrument_entry_grp_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_instrument_entry_grp_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(md_instrument_entry_grp_comp, md_entry_px) == 0, "unexpected offset of md_instrument_entry_grp_comp::md_entry_px");
static_assert(offsetof(md_instrument_entry_grp_comp, md_entry_size) == 8, "unexpected offset of md_instrument_entry_grp_comp::md_entry_size");
static_assert(offsetof(md_instrument_entry_grp_comp, md_origin_type) == 16, "unexpected offset of md_instrument_entry_grp_comp::md_origin_type");
static_assert(offsetof(md_instrument_entry_grp_comp, md_entry_type) == 17, "unexpected offset of md_instrument_entry_grp_comp::md_entry_type");
static_assert(offsetof(md_instrument_entry_grp_comp, trade_condition) == 18, "unexpected offset of md_instrument_entry_grp_comp::trade_condition");
static_assert(offsetof(md_instrument_entry_grp_comp, trd_type) == 20, "unexpected offset of md_instrument_entry_grp_comp::trd_type");
static_assert(offsetof(md_instrument_entry_grp_comp, multi_leg_reporting_type) == 22, "unexpected offset of md_instrument_entry_grp_comp::multi_leg_reporting_type");
static_assert(offsetof(md_instrument_entry_grp_comp, multi_leg_price_model) == 23, "unexpected offset of md_instrument_entry_grp_comp::multi_leg_price_model");
static_assert(offsetof(md_instrument_entry_grp_comp, non_disclosed_trade_volume) == 24, "unexpected offset of md_instrument_entry_grp_comp::non_disclosed_trade_volume");
static_assert(sizeof(md_instrument_entry_grp_comp) == 32, "unexpected sizeof md_instrument_entry_grp_comp");

#pragma pack(pop)
}
