#pragma once

#include "../types/TradeableInstrumentIdLeg.hpp"
#include "../types/SideLeg.hpp"
#include "../types/RatioLeg.hpp"
#include "../types/PriceLeg.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

struct CombinationLeg {

    TradeableInstrumentIdLeg tradeable_instrument_id_leg;
    SideLeg side_leg;
    RatioLeg ratio_leg;
    PriceLeg price_leg;

    // parse method
    static CombinationLeg* parse(std::byte* buffer) {
        return reinterpret_cast<CombinationLeg*>(buffer);
    }

    // parse method const
    static const CombinationLeg* parse(const std::byte* buffer) {
        return reinterpret_cast<const CombinationLeg*>(buffer);
    }
};

#pragma pack(pop)
}
