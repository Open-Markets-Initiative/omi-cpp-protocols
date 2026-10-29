#pragma once

#include <cstddef>
#include "../types/LegSymbol.hpp"
#include "../types/Pad4.hpp"
#include "../types/LegSecurityId.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/Pad3.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

struct instrmt_leg_grp_comp {

    fbe_eobi::leg_symbol leg_symbol;
    fbe_eobi::pad4 pad4;
    fbe_eobi::leg_security_id leg_security_id;
    fbe_eobi::leg_ratio_qty leg_ratio_qty;
    fbe_eobi::leg_side leg_side;
    fbe_eobi::pad3 pad3;

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
static_assert(offsetof(instrmt_leg_grp_comp, leg_ratio_qty) == 16, "unexpected offset of instrmt_leg_grp_comp::leg_ratio_qty");
static_assert(offsetof(instrmt_leg_grp_comp, leg_side) == 20, "unexpected offset of instrmt_leg_grp_comp::leg_side");
static_assert(offsetof(instrmt_leg_grp_comp, pad3) == 21, "unexpected offset of instrmt_leg_grp_comp::pad3");
static_assert(sizeof(instrmt_leg_grp_comp) == 24, "unexpected sizeof instrmt_leg_grp_comp");

#pragma pack(pop)
}
