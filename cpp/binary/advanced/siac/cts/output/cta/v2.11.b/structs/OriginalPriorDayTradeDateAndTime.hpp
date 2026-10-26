#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_11_b {

namespace cta_output = ::siac::cts::output::cta::v2_11_b;

#pragma pack(push, 1)

struct original_prior_day_trade_date_and_time {

    cta_output::seconds seconds;
    cta_output::nanoseconds nanoseconds;

    // parse method
    static original_prior_day_trade_date_and_time* parse(std::byte* buffer) {
        return reinterpret_cast<original_prior_day_trade_date_and_time*>(buffer);
    }

    // parse method const
    static const original_prior_day_trade_date_and_time* parse(const std::byte* buffer) {
        return reinterpret_cast<const original_prior_day_trade_date_and_time*>(buffer);
    }
};

// layout verification
static_assert(offsetof(original_prior_day_trade_date_and_time, seconds) == 0, "unexpected offset of original_prior_day_trade_date_and_time::seconds");
static_assert(offsetof(original_prior_day_trade_date_and_time, nanoseconds) == 4, "unexpected offset of original_prior_day_trade_date_and_time::nanoseconds");
static_assert(sizeof(original_prior_day_trade_date_and_time) == 8, "unexpected sizeof original_prior_day_trade_date_and_time");

#pragma pack(pop)
}
