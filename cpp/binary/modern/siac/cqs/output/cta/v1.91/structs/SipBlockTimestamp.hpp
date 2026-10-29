#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cqs::output::cta::v1_91 {

#pragma pack(push, 1)

struct SipBlockTimestamp {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static SipBlockTimestamp* parse(std::byte* buffer) {
        return reinterpret_cast<SipBlockTimestamp*>(buffer);
    }

    // parse method const
    static const SipBlockTimestamp* parse(const std::byte* buffer) {
        return reinterpret_cast<const SipBlockTimestamp*>(buffer);
    }
};

#pragma pack(pop)
}
