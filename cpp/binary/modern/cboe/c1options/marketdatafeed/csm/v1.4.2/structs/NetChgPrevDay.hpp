// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/NetChgPrevDay.hpp
#pragma once

#include "../types/NetChgPrevDayExponent.hpp"
#include "../types/NetChgPrevDayMantissa.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct NetChgPrevDay {

    NetChgPrevDayExponent net_chg_prev_day_exponent;
    NetChgPrevDayMantissa net_chg_prev_day_mantissa;

    // parse method
    static NetChgPrevDay* parse(std::byte* buffer) {
        return reinterpret_cast<NetChgPrevDay*>(buffer);
    }

    // parse method const
    static const NetChgPrevDay* parse(const std::byte* buffer) {
        return reinterpret_cast<const NetChgPrevDay*>(buffer);
    }
};

#pragma pack(pop)
}
