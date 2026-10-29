#pragma once

#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastParticipantId.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct ParticipantData {

    PreviousClosePriceDate previous_close_price_date;
    LastParticipantId last_participant_id;
    LastPrice last_price;
    HighPrice high_price;
    LowPrice low_price;
    TotalVolume total_volume;
    Tick tick;

    // parse method
    static ParticipantData* parse(std::byte* buffer) {
        return reinterpret_cast<ParticipantData*>(buffer);
    }

    // parse method const
    static const ParticipantData* parse(const std::byte* buffer) {
        return reinterpret_cast<const ParticipantData*>(buffer);
    }
};

#pragma pack(pop)
}
