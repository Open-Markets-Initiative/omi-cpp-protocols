#pragma once

#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastParticipantId.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/FractionalTotalVolume.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct FractionalConsolidatedData {

    PreviousClosePriceDate previous_close_price_date;
    LastParticipantId last_participant_id;
    LastPrice last_price;
    HighPrice high_price;
    LowPrice low_price;
    FractionalTotalVolume fractional_total_volume;
    Tick tick;

    // parse method
    static FractionalConsolidatedData* parse(std::byte* buffer) {
        return reinterpret_cast<FractionalConsolidatedData*>(buffer);
    }

    // parse method const
    static const FractionalConsolidatedData* parse(const std::byte* buffer) {
        return reinterpret_cast<const FractionalConsolidatedData*>(buffer);
    }
};

#pragma pack(pop)
}
