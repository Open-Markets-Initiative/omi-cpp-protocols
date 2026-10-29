#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cqs::output::cta::v1_91 {

namespace cta_output = ::siac::cqs::output::cta::v1_91;

#pragma pack(push, 1)

struct adf_timestamp {

    cta_output::seconds seconds;
    cta_output::nanoseconds nanoseconds;

    // parse method
    static adf_timestamp* parse(std::byte* buffer) {
        return reinterpret_cast<adf_timestamp*>(buffer);
    }

    // parse method const
    static const adf_timestamp* parse(const std::byte* buffer) {
        return reinterpret_cast<const adf_timestamp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(adf_timestamp, seconds) == 0, "unexpected offset of adf_timestamp::seconds");
static_assert(offsetof(adf_timestamp, nanoseconds) == 4, "unexpected offset of adf_timestamp::nanoseconds");
static_assert(sizeof(adf_timestamp) == 8, "unexpected sizeof adf_timestamp");

#pragma pack(pop)
}
