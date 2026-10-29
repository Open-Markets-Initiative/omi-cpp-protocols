#pragma once

#include <cstddef>
#include "../types/LegSecurityId.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/Pad3.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

struct instrmt_leg_grp {

    fbe_eobi::leg_security_id leg_security_id;
    fbe_eobi::leg_ratio_qty leg_ratio_qty;
    fbe_eobi::leg_side leg_side;
    fbe_eobi::pad_3 pad_3;

    // parse method
    static instrmt_leg_grp* parse(std::byte* buffer) {
        return reinterpret_cast<instrmt_leg_grp*>(buffer);
    }

    // parse method const
    static const instrmt_leg_grp* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrmt_leg_grp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(instrmt_leg_grp, leg_security_id) == 0, "unexpected offset of instrmt_leg_grp::leg_security_id");
static_assert(offsetof(instrmt_leg_grp, leg_ratio_qty) == 8, "unexpected offset of instrmt_leg_grp::leg_ratio_qty");
static_assert(offsetof(instrmt_leg_grp, leg_side) == 12, "unexpected offset of instrmt_leg_grp::leg_side");
static_assert(offsetof(instrmt_leg_grp, pad_3) == 13, "unexpected offset of instrmt_leg_grp::pad_3");
static_assert(sizeof(instrmt_leg_grp) == 16, "unexpected sizeof instrmt_leg_grp");

#pragma pack(pop)
}
