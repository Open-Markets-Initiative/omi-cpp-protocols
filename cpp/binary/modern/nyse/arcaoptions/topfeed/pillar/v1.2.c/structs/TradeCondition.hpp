#pragma once

#include "../types/Series.hpp"
#include "../types/Opening.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Offical.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

#pragma pack(push, 1)

struct TradeCondition {

    Series series;
    Opening opening;
    Reserved1 reserved_1;
    Offical offical;

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
