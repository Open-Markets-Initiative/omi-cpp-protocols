#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::opra::output::obi::v6_2 {

namespace obi_output = ::siac::opra::output::obi::v6_2;

#pragma pack(push, 1)

struct block_timestamp {

    obi_output::seconds seconds;
    obi_output::nanoseconds nanoseconds;

    // parse method
    static block_timestamp* parse(std::byte* buffer) {
        return reinterpret_cast<block_timestamp*>(buffer);
    }

    // parse method const
    static const block_timestamp* parse(const std::byte* buffer) {
        return reinterpret_cast<const block_timestamp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(block_timestamp, seconds) == 0, "unexpected offset of block_timestamp::seconds");
static_assert(offsetof(block_timestamp, nanoseconds) == 4, "unexpected offset of block_timestamp::nanoseconds");
static_assert(sizeof(block_timestamp) == 8, "unexpected sizeof block_timestamp");

#pragma pack(pop)
}
