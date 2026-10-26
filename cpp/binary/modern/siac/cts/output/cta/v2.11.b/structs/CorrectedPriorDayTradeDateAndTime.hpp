#pragma once

#include "../types/Seconds.hpp"
#include "../types/Nanoseconds.hpp"

namespace siac::cts::output::cta::v2_11_b {

#pragma pack(push, 1)

struct CorrectedPriorDayTradeDateAndTime {

    Seconds seconds;
    Nanoseconds nanoseconds;

    // parse method
    static CorrectedPriorDayTradeDateAndTime* parse(std::byte* buffer) {
        return reinterpret_cast<CorrectedPriorDayTradeDateAndTime*>(buffer);
    }

    // parse method const
    static const CorrectedPriorDayTradeDateAndTime* parse(const std::byte* buffer) {
        return reinterpret_cast<const CorrectedPriorDayTradeDateAndTime*>(buffer);
    }
};

#pragma pack(pop)
}
