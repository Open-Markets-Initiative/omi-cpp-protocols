#pragma once

#include "../types/InstrumentId.hpp"
#include "../types/LegRatioAndSide.hpp"
#include "../types/MaturityMonthYear.hpp"
#include "../types/Reserved8.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

#pragma pack(push, 1)

struct InstrumentLeg {

    InstrumentId instrument_id;
    LegRatioAndSide leg_ratio_and_side;
    MaturityMonthYear maturity_month_year;
    Reserved8 reserved_8;

    // parse method
    static InstrumentLeg* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentLeg*>(buffer);
    }

    // parse method const
    static const InstrumentLeg* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentLeg*>(buffer);
    }
};

#pragma pack(pop)
}
