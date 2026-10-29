#pragma once

#include <cstddef>
#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastParticipantId.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v1_91 {

namespace cta_output = ::siac::cts::output::cta::v1_91;

#pragma pack(push, 1)

struct participant_data {

    cta_output::previous_close_price_date previous_close_price_date;
    cta_output::last_participant_id last_participant_id;
    cta_output::last_price last_price;
    cta_output::high_price high_price;
    cta_output::low_price low_price;
    cta_output::total_volume total_volume;
    cta_output::tick tick;

    // parse method
    static participant_data* parse(std::byte* buffer) {
        return reinterpret_cast<participant_data*>(buffer);
    }

    // parse method const
    static const participant_data* parse(const std::byte* buffer) {
        return reinterpret_cast<const participant_data*>(buffer);
    }
};

// layout verification
static_assert(offsetof(participant_data, previous_close_price_date) == 0, "unexpected offset of participant_data::previous_close_price_date");
static_assert(offsetof(participant_data, last_participant_id) == 4, "unexpected offset of participant_data::last_participant_id");
static_assert(offsetof(participant_data, last_price) == 5, "unexpected offset of participant_data::last_price");
static_assert(offsetof(participant_data, high_price) == 13, "unexpected offset of participant_data::high_price");
static_assert(offsetof(participant_data, low_price) == 21, "unexpected offset of participant_data::low_price");
static_assert(offsetof(participant_data, total_volume) == 29, "unexpected offset of participant_data::total_volume");
static_assert(offsetof(participant_data, tick) == 37, "unexpected offset of participant_data::tick");
static_assert(sizeof(participant_data) == 38, "unexpected sizeof participant_data");

#pragma pack(pop)
}
