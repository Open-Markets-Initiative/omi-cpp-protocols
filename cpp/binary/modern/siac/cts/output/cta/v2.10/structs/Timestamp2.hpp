#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct Timestamp2 {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static Timestamp2* parse(std::byte* buffer) {
        return reinterpret_cast<Timestamp2*>(buffer);
    }

    // parse method const
    static const Timestamp2* parse(const std::byte* buffer) {
        return reinterpret_cast<const Timestamp2*>(buffer);
    }
};

#pragma pack(pop)
}
