#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_9 {

namespace cta_output = ::siac::cts::output::cta::v2_9;

#pragma pack(push, 1)

struct timestamp_2 {

    cta_output::seconds seconds;
    cta_output::nanoseconds nanoseconds;

    // parse method
    static timestamp_2* parse(std::byte* buffer) {
        return reinterpret_cast<timestamp_2*>(buffer);
    }

    // parse method const
    static const timestamp_2* parse(const std::byte* buffer) {
        return reinterpret_cast<const timestamp_2*>(buffer);
    }
};

// layout verification
static_assert(offsetof(timestamp_2, seconds) == 0, "unexpected offset of timestamp_2::seconds");
static_assert(offsetof(timestamp_2, nanoseconds) == 4, "unexpected offset of timestamp_2::nanoseconds");
static_assert(sizeof(timestamp_2) == 8, "unexpected sizeof timestamp_2");

#pragma pack(pop)
}
