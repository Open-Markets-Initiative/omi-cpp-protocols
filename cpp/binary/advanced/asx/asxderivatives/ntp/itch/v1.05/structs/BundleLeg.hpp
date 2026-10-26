#pragma once

#include <cstddef>
#include "../types/TradeableInstrumentIdLeg.hpp"
#include "../types/SideLeg.hpp"
#include "../types/RatioLeg.hpp"
#include "../types/PriceLeg.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

struct bundle_leg {

    itch_ntp::tradeable_instrument_id_leg tradeable_instrument_id_leg;
    itch_ntp::side_leg side_leg;
    itch_ntp::ratio_leg ratio_leg;
    itch_ntp::price_leg price_leg;

    // parse method
    static bundle_leg* parse(std::byte* buffer) {
        return reinterpret_cast<bundle_leg*>(buffer);
    }

    // parse method const
    static const bundle_leg* parse(const std::byte* buffer) {
        return reinterpret_cast<const bundle_leg*>(buffer);
    }
};

// layout verification
static_assert(offsetof(bundle_leg, tradeable_instrument_id_leg) == 0, "unexpected offset of bundle_leg::tradeable_instrument_id_leg");
static_assert(offsetof(bundle_leg, side_leg) == 4, "unexpected offset of bundle_leg::side_leg");
static_assert(offsetof(bundle_leg, ratio_leg) == 5, "unexpected offset of bundle_leg::ratio_leg");
static_assert(offsetof(bundle_leg, price_leg) == 9, "unexpected offset of bundle_leg::price_leg");
static_assert(sizeof(bundle_leg) == 17, "unexpected sizeof bundle_leg");

#pragma pack(pop)
}
