#pragma once

#include <cstddef>
#include "../types/LegSymbol.hpp"
#include "../types/Pad4.hpp"
#include "../types/LegSecurityId.hpp"
#include "../types/LegPrice.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSecurityType.hpp"
#include "../types/LegSide.hpp"
#include "../types/RelatedPriceType.hpp"
#include "../types/TradingStyle.hpp"
#include "../types/RelatedPrice.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

struct instrmt_leg_grp_comp {

    fbe_eobi::leg_symbol leg_symbol;
    fbe_eobi::pad4 pad4;
    fbe_eobi::leg_security_id leg_security_id;
    fbe_eobi::leg_price leg_price;
    fbe_eobi::leg_ratio_qty leg_ratio_qty;
    fbe_eobi::leg_security_type leg_security_type;
    fbe_eobi::leg_side leg_side;
    fbe_eobi::related_price_type related_price_type;
    fbe_eobi::trading_style trading_style;
    fbe_eobi::related_price related_price;

    // parse method
    static instrmt_leg_grp_comp* parse(std::byte* buffer) {
        return reinterpret_cast<instrmt_leg_grp_comp*>(buffer);
    }

    // parse method const
    static const instrmt_leg_grp_comp* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrmt_leg_grp_comp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(instrmt_leg_grp_comp, leg_symbol) == 0, "unexpected offset of instrmt_leg_grp_comp::leg_symbol");
static_assert(offsetof(instrmt_leg_grp_comp, pad4) == 4, "unexpected offset of instrmt_leg_grp_comp::pad4");
static_assert(offsetof(instrmt_leg_grp_comp, leg_security_id) == 8, "unexpected offset of instrmt_leg_grp_comp::leg_security_id");
static_assert(offsetof(instrmt_leg_grp_comp, leg_price) == 16, "unexpected offset of instrmt_leg_grp_comp::leg_price");
static_assert(offsetof(instrmt_leg_grp_comp, leg_ratio_qty) == 24, "unexpected offset of instrmt_leg_grp_comp::leg_ratio_qty");
static_assert(offsetof(instrmt_leg_grp_comp, leg_security_type) == 28, "unexpected offset of instrmt_leg_grp_comp::leg_security_type");
static_assert(offsetof(instrmt_leg_grp_comp, leg_side) == 29, "unexpected offset of instrmt_leg_grp_comp::leg_side");
static_assert(offsetof(instrmt_leg_grp_comp, related_price_type) == 30, "unexpected offset of instrmt_leg_grp_comp::related_price_type");
static_assert(offsetof(instrmt_leg_grp_comp, trading_style) == 31, "unexpected offset of instrmt_leg_grp_comp::trading_style");
static_assert(offsetof(instrmt_leg_grp_comp, related_price) == 32, "unexpected offset of instrmt_leg_grp_comp::related_price");
static_assert(sizeof(instrmt_leg_grp_comp) == 40, "unexpected sizeof instrmt_leg_grp_comp");

#pragma pack(pop)
}
