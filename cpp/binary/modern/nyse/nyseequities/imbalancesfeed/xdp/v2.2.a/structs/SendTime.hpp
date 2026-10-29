#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

#pragma pack(push, 1)

struct SendTime {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static SendTime* parse(std::byte* buffer) {
        return reinterpret_cast<SendTime*>(buffer);
    }

    // parse method const
    static const SendTime* parse(const std::byte* buffer) {
        return reinterpret_cast<const SendTime*>(buffer);
    }
};

#pragma pack(pop)
}
