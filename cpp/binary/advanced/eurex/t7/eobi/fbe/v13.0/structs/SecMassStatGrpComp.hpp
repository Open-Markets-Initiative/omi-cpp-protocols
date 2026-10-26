#pragma once

#include <cstddef>
#include "../types/SecurityId.hpp"
#include "../types/HighPx.hpp"
#include "../types/LowPx.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/SoldOutIndicator.hpp"
#include "../types/TesSecurityStatus.hpp"
#include "../types/Pad2.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v13_0;

#pragma pack(push, 1)

struct sec_mass_stat_grp_comp {

    fbe_eobi::security_id security_id;
    fbe_eobi::high_px high_px;
    fbe_eobi::low_px low_px;
    fbe_eobi::security_status security_status;
    fbe_eobi::security_trading_status security_trading_status;
    fbe_eobi::market_condition market_condition;
    fbe_eobi::security_trading_event security_trading_event;
    fbe_eobi::sold_out_indicator sold_out_indicator;
    fbe_eobi::tes_security_status tes_security_status;
    fbe_eobi::pad2 pad2;

    // parse method
    static sec_mass_stat_grp_comp* parse(std::byte* buffer) {
        return reinterpret_cast<sec_mass_stat_grp_comp*>(buffer);
    }

    // parse method const
    static const sec_mass_stat_grp_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const sec_mass_stat_grp_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(sec_mass_stat_grp_comp, security_id) == 0, "unexpected offset of sec_mass_stat_grp_comp::security_id");
static_assert(offsetof(sec_mass_stat_grp_comp, high_px) == 8, "unexpected offset of sec_mass_stat_grp_comp::high_px");
static_assert(offsetof(sec_mass_stat_grp_comp, low_px) == 16, "unexpected offset of sec_mass_stat_grp_comp::low_px");
static_assert(offsetof(sec_mass_stat_grp_comp, security_status) == 24, "unexpected offset of sec_mass_stat_grp_comp::security_status");
static_assert(offsetof(sec_mass_stat_grp_comp, security_trading_status) == 25, "unexpected offset of sec_mass_stat_grp_comp::security_trading_status");
static_assert(offsetof(sec_mass_stat_grp_comp, market_condition) == 26, "unexpected offset of sec_mass_stat_grp_comp::market_condition");
static_assert(offsetof(sec_mass_stat_grp_comp, security_trading_event) == 27, "unexpected offset of sec_mass_stat_grp_comp::security_trading_event");
static_assert(offsetof(sec_mass_stat_grp_comp, sold_out_indicator) == 28, "unexpected offset of sec_mass_stat_grp_comp::sold_out_indicator");
static_assert(offsetof(sec_mass_stat_grp_comp, tes_security_status) == 29, "unexpected offset of sec_mass_stat_grp_comp::tes_security_status");
static_assert(offsetof(sec_mass_stat_grp_comp, pad2) == 30, "unexpected offset of sec_mass_stat_grp_comp::pad2");
static_assert(sizeof(sec_mass_stat_grp_comp) == 32, "unexpected sizeof sec_mass_stat_grp_comp");

#pragma pack(pop)
}
