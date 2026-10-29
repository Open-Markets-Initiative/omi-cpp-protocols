#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_9 {

namespace cta_output = ::siac::cts::output::cta::v2_9;

#pragma pack(push, 1)

struct timestamp_1 {

    cta_output::seconds seconds;
    cta_output::nanoseconds nanoseconds;

    // parse method
    static timestamp_1* parse(std::byte* buffer) {
        return reinterpret_cast<timestamp_1*>(buffer);
    }

    // parse method const
    static const timestamp_1* parse(const std::byte* buffer) {
        return reinterpret_cast<const timestamp_1*>(buffer);
    }
};

// layout verification
static_assert(offsetof(timestamp_1, seconds) == 0, "unexpected offset of timestamp_1::seconds");
static_assert(offsetof(timestamp_1, nanoseconds) == 4, "unexpected offset of timestamp_1::nanoseconds");
static_assert(sizeof(timestamp_1) == 8, "unexpected sizeof timestamp_1");

#pragma pack(pop)
}
