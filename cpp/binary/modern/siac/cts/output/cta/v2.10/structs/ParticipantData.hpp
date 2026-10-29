#pragma once

#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/TotalVolumeShort.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct ParticipantData {

    PreviousClosePriceDate previous_close_price_date;
    LastPrice last_price;
    HighPrice high_price;
    LowPrice low_price;
    OpenPrice open_price;
    TotalVolumeShort total_volume_short;
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
