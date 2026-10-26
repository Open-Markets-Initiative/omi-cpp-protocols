#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

struct Timestamp1 {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static Timestamp1* parse(std::byte* buffer) {
        return reinterpret_cast<Timestamp1*>(buffer);
    }

    // parse method const
    static const Timestamp1* parse(const std::byte* buffer) {
        return reinterpret_cast<const Timestamp1*>(buffer);
    }
};

#pragma pack(pop)
}
