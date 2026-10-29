#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

struct sip_block_timestamp {

    cta_output::seconds seconds;
    cta_output::nanoseconds nanoseconds;

    // parse method
    static sip_block_timestamp* parse(std::byte* buffer) {
        return reinterpret_cast<sip_block_timestamp*>(buffer);
    }

    // parse method const
    static const sip_block_timestamp* parse(const std::byte* buffer) {
        return reinterpret_cast<const sip_block_timestamp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(sip_block_timestamp, seconds) == 0, "unexpected offset of sip_block_timestamp::seconds");
static_assert(offsetof(sip_block_timestamp, nanoseconds) == 4, "unexpected offset of sip_block_timestamp::nanoseconds");
static_assert(sizeof(sip_block_timestamp) == 8, "unexpected sizeof sip_block_timestamp");

#pragma pack(pop)
}
