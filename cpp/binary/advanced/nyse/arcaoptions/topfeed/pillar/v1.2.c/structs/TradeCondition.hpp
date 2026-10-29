#pragma once

#include <cstddef>
#include "../types/Series.hpp"
#include "../types/Opening.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Offical.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

struct trade_condition {

    pillar_topfeed::series series;
    pillar_topfeed::opening opening;
    pillar_topfeed::reserved_1 reserved_1;
    pillar_topfeed::offical offical;

    // parse method
    static trade_condition* parse(std::byte* buffer) {
        return reinterpret_cast<trade_condition*>(buffer);
    }

    // parse method const
    static const trade_condition* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_condition*>(buffer);
    }
};

// layout verification
static_assert(offsetof(trade_condition, series) == 0, "unexpected offset of trade_condition::series");
static_assert(offsetof(trade_condition, opening) == 1, "unexpected offset of trade_condition::opening");
static_assert(offsetof(trade_condition, reserved_1) == 2, "unexpected offset of trade_condition::reserved_1");
static_assert(offsetof(trade_condition, offical) == 3, "unexpected offset of trade_condition::offical");
static_assert(sizeof(trade_condition) == 4, "unexpected sizeof trade_condition");

#pragma pack(pop)
}
