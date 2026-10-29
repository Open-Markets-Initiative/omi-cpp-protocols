#pragma once

#include <cstddef>
#include "../types/PreviousClosePriceDate.hpp"
#include "../types/LastPrice.hpp"
#include "../types/HighPrice.hpp"
#include "../types/LowPrice.hpp"
#include "../types/OpenPrice.hpp"
#include "../types/FractionalTotalVolume.hpp"
#include "../types/Tick.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

struct fractional_participant_data {

    cta_output::previous_close_price_date previous_close_price_date;
    cta_output::last_price last_price;
    cta_output::high_price high_price;
    cta_output::low_price low_price;
    cta_output::open_price open_price;
    cta_output::fractional_total_volume fractional_total_volume;
    cta_output::tick tick;

    // parse method
    static fractional_participant_data* parse(std::byte* buffer) {
        return reinterpret_cast<fractional_participant_data*>(buffer);
    }

    // parse method const
    static const fractional_participant_data* parse(const std::byte* buffer) {
        return reinterpret_cast<const fractional_participant_data*>(buffer);
    }
};

// layout verification
static_assert(offsetof(fractional_participant_data, previous_close_price_date) == 0, "unexpected offset of fractional_participant_data::previous_close_price_date");
static_assert(offsetof(fractional_participant_data, last_price) == 4, "unexpected offset of fractional_participant_data::last_price");
static_assert(offsetof(fractional_participant_data, high_price) == 12, "unexpected offset of fractional_participant_data::high_price");
static_assert(offsetof(fractional_participant_data, low_price) == 20, "unexpected offset of fractional_participant_data::low_price");
static_assert(offsetof(fractional_participant_data, open_price) == 28, "unexpected offset of fractional_participant_data::open_price");
static_assert(offsetof(fractional_participant_data, fractional_total_volume) == 36, "unexpected offset of fractional_participant_data::fractional_total_volume");
static_assert(offsetof(fractional_participant_data, tick) == 44, "unexpected offset of fractional_participant_data::tick");
static_assert(sizeof(fractional_participant_data) == 45, "unexpected sizeof fractional_participant_data");

#pragma pack(pop)
}
