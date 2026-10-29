#pragma once

#include <cstddef>
#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cqs::output::cta::v1_91 {

namespace cta_output = ::siac::cqs::output::cta::v1_91;

#pragma pack(push, 1)

struct participant_timestamp {

    cta_output::seconds seconds;
    cta_output::nanoseconds nanoseconds;

    // parse method
    static participant_timestamp* parse(std::byte* buffer) {
        return reinterpret_cast<participant_timestamp*>(buffer);
    }

    // parse method const
    static const participant_timestamp* parse(const std::byte* buffer) {
        return reinterpret_cast<const participant_timestamp*>(buffer);
    }
};

// layout verification
static_assert(offsetof(participant_timestamp, seconds) == 0, "unexpected offset of participant_timestamp::seconds");
static_assert(offsetof(participant_timestamp, nanoseconds) == 4, "unexpected offset of participant_timestamp::nanoseconds");
static_assert(sizeof(participant_timestamp) == 8, "unexpected sizeof participant_timestamp");

#pragma pack(pop)
}
