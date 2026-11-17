// Cboe.C1Options.MarketDataFeed.Csm.v1.4.2: structs/TradeCondition.hpp
#pragma once

#include "../types/TradeConditionLength.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

#pragma pack(push, 1)

struct TradeCondition {

    TradeConditionLength trade_condition_length;

    // parse method
    static TradeCondition* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCondition*>(buffer);
    }

    // parse method const
    static const TradeCondition* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCondition*>(buffer);
    }
};

#pragma pack(pop)
}
