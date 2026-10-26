#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

struct corrected_prior_day_trade_date_and_time {

    cta_output::seconds seconds;
    cta_output::nanoseconds nanoseconds;

    // parse method
    static corrected_prior_day_trade_date_and_time* parse(std::byte* buffer) {
        return reinterpret_cast<corrected_prior_day_trade_date_and_time*>(buffer);
    }

    // parse method const
    static const corrected_prior_day_trade_date_and_time* parse(const std::byte* buffer) {
        return reinterpret_cast<const corrected_prior_day_trade_date_and_time*>(buffer);
    }
};

// layout verification
static_assert(offsetof(corrected_prior_day_trade_date_and_time, seconds) == 0, "unexpected offset of corrected_prior_day_trade_date_and_time::seconds");
static_assert(offsetof(corrected_prior_day_trade_date_and_time, nanoseconds) == 4, "unexpected offset of corrected_prior_day_trade_date_and_time::nanoseconds");
static_assert(sizeof(corrected_prior_day_trade_date_and_time) == 8, "unexpected sizeof corrected_prior_day_trade_date_and_time");

#pragma pack(pop)
}
