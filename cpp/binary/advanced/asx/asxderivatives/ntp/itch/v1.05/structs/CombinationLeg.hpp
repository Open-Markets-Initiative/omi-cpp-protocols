#pragma once

#include <cstddef>
#include "../types/TradeableInstrumentIdLeg.hpp"
#include "../types/SideLeg.hpp"
#include "../types/RatioLeg.hpp"
#include "../types/PriceLeg.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

struct combination_leg {

    itch_ntp::tradeable_instrument_id_leg tradeable_instrument_id_leg;
    itch_ntp::side_leg side_leg;
    itch_ntp::ratio_leg ratio_leg;
    itch_ntp::price_leg price_leg;

    // parse method
    static combination_leg* parse(std::byte* buffer) {
        return reinterpret_cast<combination_leg*>(buffer);
    }

    // parse method const
    static const combination_leg* parse(const std::byte* buffer) {
        return reinterpret_cast<const combination_leg*>(buffer);
    }
};

// layout verification
static_assert(offsetof(combination_leg, tradeable_instrument_id_leg) == 0, "unexpected offset of combination_leg::tradeable_instrument_id_leg");
static_assert(offsetof(combination_leg, side_leg) == 4, "unexpected offset of combination_leg::side_leg");
static_assert(offsetof(combination_leg, ratio_leg) == 5, "unexpected offset of combination_leg::ratio_leg");
static_assert(offsetof(combination_leg, price_leg) == 9, "unexpected offset of combination_leg::price_leg");
static_assert(sizeof(combination_leg) == 17, "unexpected sizeof combination_leg");

#pragma pack(pop)
}
