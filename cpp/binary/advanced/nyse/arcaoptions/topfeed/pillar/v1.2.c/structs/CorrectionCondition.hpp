#pragma once

#include <cstddef>
#include "../types/Transaction.hpp"
#include "../types/Reserved3.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

struct correction_condition {

    pillar_topfeed::transaction transaction;
    pillar_topfeed::reserved_3 reserved_3;

    // parse method
    static correction_condition* parse(std::byte* buffer) {
        return reinterpret_cast<correction_condition*>(buffer);
    }

    // parse method const
    static const correction_condition* parse(const std::byte* buffer) {
        return reinterpret_cast<const correction_condition*>(buffer);
    }
};

// layout verification
static_assert(offsetof(correction_condition, transaction) == 0, "unexpected offset of correction_condition::transaction");
static_assert(offsetof(correction_condition, reserved_3) == 1, "unexpected offset of correction_condition::reserved_3");
static_assert(sizeof(correction_condition) == 4, "unexpected sizeof correction_condition");

#pragma pack(pop)
}
