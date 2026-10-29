#pragma once

#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastParticipantId.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/TotalVolumeShort.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v2_9 {

#pragma pack(push, 1)

struct ConsolidatedData {

    PreviousClosePriceDate previous_close_price_date;
    LastParticipantId last_participant_id;
    LastPrice last_price;
    HighPrice high_price;
    LowPrice low_price;
    TotalVolumeShort total_volume_short;
    Tick tick;

    // parse method
    static ConsolidatedData* parse(std::byte* buffer) {
        return reinterpret_cast<ConsolidatedData*>(buffer);
    }

    // parse method const
    static const ConsolidatedData* parse(const std::byte* buffer) {
        return reinterpret_cast<const ConsolidatedData*>(buffer);
    }
};

#pragma pack(pop)
}
