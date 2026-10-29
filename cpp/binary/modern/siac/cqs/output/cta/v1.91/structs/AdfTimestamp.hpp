#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

struct AdfTimestamp {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static AdfTimestamp* parse(std::byte* buffer) {
        return reinterpret_cast<AdfTimestamp*>(buffer);
    }

    // parse method const
    static const AdfTimestamp* parse(const std::byte* buffer) {
        return reinterpret_cast<const AdfTimestamp*>(buffer);
    }
};

#pragma pack(pop)
}
