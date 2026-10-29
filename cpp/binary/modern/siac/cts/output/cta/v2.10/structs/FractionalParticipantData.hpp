#pragma once

#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/FractionalTotalVolume.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct FractionalParticipantData {

    PreviousClosePriceDate previous_close_price_date;
    LastPrice last_price;
    HighPrice high_price;
    LowPrice low_price;
    OpenPrice open_price;
    FractionalTotalVolume fractional_total_volume;
    Tick tick;

    // parse method
    static FractionalParticipantData* parse(std::byte* buffer) {
        return reinterpret_cast<FractionalParticipantData*>(buffer);
    }

    // parse method const
    static const FractionalParticipantData* parse(const std::byte* buffer) {
        return reinterpret_cast<const FractionalParticipantData*>(buffer);
    }
};

#pragma pack(pop)
}
