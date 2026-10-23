#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

struct OriginalPriorDayTradeDateAndTime {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static OriginalPriorDayTradeDateAndTime* parse(std::byte* buffer) {
        return reinterpret_cast<OriginalPriorDayTradeDateAndTime*>(buffer);
    }

    // parse method const
    static const OriginalPriorDayTradeDateAndTime* parse(const std::byte* buffer) {
        return reinterpret_cast<const OriginalPriorDayTradeDateAndTime*>(buffer);
    }
};

#pragma pack(pop)
}
