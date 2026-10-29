#pragma once

#include <cstddef>
#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastParticipantId.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/TotalVolumeShort.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

struct consolidated_data {

    cta_output::previous_close_price_date previous_close_price_date;
    cta_output::last_participant_id last_participant_id;
    cta_output::last_price last_price;
    cta_output::high_price high_price;
    cta_output::low_price low_price;
    cta_output::total_volume_short total_volume_short;
    cta_output::tick tick;

    // parse method
    static consolidated_data* parse(std::byte* buffer) {
        return reinterpret_cast<consolidated_data*>(buffer);
    }

    // parse method const
    static const consolidated_data* parse(const std::byte* buffer) {
        return reinterpret_cast<const consolidated_data*>(buffer);
    }
};

// layout verification
static_assert(offsetof(consolidated_data, previous_close_price_date) == 0, "unexpected offset of consolidated_data::previous_close_price_date");
static_assert(offsetof(consolidated_data, last_participant_id) == 4, "unexpected offset of consolidated_data::last_participant_id");
static_assert(offsetof(consolidated_data, last_price) == 5, "unexpected offset of consolidated_data::last_price");
static_assert(offsetof(consolidated_data, high_price) == 13, "unexpected offset of consolidated_data::high_price");
static_assert(offsetof(consolidated_data, low_price) == 21, "unexpected offset of consolidated_data::low_price");
static_assert(offsetof(consolidated_data, total_volume_short) == 29, "unexpected offset of consolidated_data::total_volume_short");
static_assert(offsetof(consolidated_data, tick) == 33, "unexpected offset of consolidated_data::tick");
static_assert(sizeof(consolidated_data) == 34, "unexpected sizeof consolidated_data");

#pragma pack(pop)
}
