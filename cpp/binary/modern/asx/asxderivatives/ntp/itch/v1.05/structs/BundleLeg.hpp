#pragma once

#include "../types/TradeableInstrumentIdLeg.hpp"
#include "../types/SideLeg.hpp"
#include "../types/RatioLeg.hpp"
#include "../types/PriceLeg.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

struct BundleLeg {

    TradeableInstrumentIdLeg tradeable_instrument_id_leg;
    SideLeg side_leg;
    RatioLeg ratio_leg;
    PriceLeg price_leg;

    // parse method
    static BundleLeg* parse(std::byte* buffer) {
        return reinterpret_cast<BundleLeg*>(buffer);
    }

    // parse method const
    static const BundleLeg* parse(const std::byte* buffer) {
        return reinterpret_cast<const BundleLeg*>(buffer);
    }
};

#pragma pack(pop)
}
