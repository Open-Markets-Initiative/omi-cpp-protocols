#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

#pragma pack(push, 1)

struct send_time {

    xdp_complexfeed::seconds seconds;
    xdp_complexfeed::nanoseconds nanoseconds;

    // parse method
    static send_time* parse(std::byte* buffer) {
        return reinterpret_cast<send_time*>(buffer);
    }

    // parse method const
    static const send_time* parse(const std::byte* buffer) {
        return reinterpret_cast<const send_time*>(buffer);
    }
};

// layout verification
static_assert(offsetof(send_time, seconds) == 0, "unexpected offset of send_time::seconds");
static_assert(offsetof(send_time, nanoseconds) == 4, "unexpected offset of send_time::nanoseconds");
static_assert(sizeof(send_time) == 8, "unexpected sizeof send_time");

#pragma pack(pop)
}
