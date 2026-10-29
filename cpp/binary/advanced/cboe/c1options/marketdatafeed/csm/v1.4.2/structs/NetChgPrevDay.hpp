#pragma once

#include <cstddef>
#include "../types/NetChgPrevDayExponent.hpp"
#include "../types/NetChgPrevDayMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

namespace csm_marketdatafeed = ::cboe::c1options::marketdatafeed::csm::v1_4_2;

#pragma pack(push, 1)

struct net_chg_prev_day {

    csm_marketdatafeed::net_chg_prev_day_exponent net_chg_prev_day_exponent;
    csm_marketdatafeed::net_chg_prev_day_mantissa net_chg_prev_day_mantissa;

    // parse method
    static net_chg_prev_day* parse(std::byte* buffer) {
        return reinterpret_cast<net_chg_prev_day*>(buffer);
    }

    // parse method const
    static const net_chg_prev_day* parse(const std::byte* buffer) {
        return reinterpret_cast<const net_chg_prev_day*>(buffer);
    }
};

// layout verification
static_assert(offsetof(net_chg_prev_day, net_chg_prev_day_exponent) == 0, "unexpected offset of net_chg_prev_day::net_chg_prev_day_exponent");
static_assert(offsetof(net_chg_prev_day, net_chg_prev_day_mantissa) == 1, "unexpected offset of net_chg_prev_day::net_chg_prev_day_mantissa");
static_assert(sizeof(net_chg_prev_day) == 5, "unexpected sizeof net_chg_prev_day");

#pragma pack(pop)
}
