#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

struct ParticipantTimestamp {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static ParticipantTimestamp* parse(std::byte* buffer) {
        return reinterpret_cast<ParticipantTimestamp*>(buffer);
    }

    // parse method const
    static const ParticipantTimestamp* parse(const std::byte* buffer) {
        return reinterpret_cast<const ParticipantTimestamp*>(buffer);
    }
};

#pragma pack(pop)
}
