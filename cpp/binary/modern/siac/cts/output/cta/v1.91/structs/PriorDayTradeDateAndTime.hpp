#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v1_91 {

#pragma pack(push, 1)

struct PriorDayTradeDateAndTime {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static PriorDayTradeDateAndTime* parse(std::byte* buffer) {
        return reinterpret_cast<PriorDayTradeDateAndTime*>(buffer);
    }

    // parse method const
    static const PriorDayTradeDateAndTime* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriorDayTradeDateAndTime*>(buffer);
    }
};

#pragma pack(pop)
}
