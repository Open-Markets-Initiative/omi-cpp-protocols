#pragma once

#include "../types/EquityAndIndexEndOfDaySummaryMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct EquityAndIndexEndOfDaySummaryCategory {

    EquityAndIndexEndOfDaySummaryMessageType equity_and_index_end_of_day_summary_message_type;

    // parse method
    static EquityAndIndexEndOfDaySummaryCategory* parse(std::byte* buffer) {
        return reinterpret_cast<EquityAndIndexEndOfDaySummaryCategory*>(buffer);
    }

    // parse method const
    static const EquityAndIndexEndOfDaySummaryCategory* parse(const std::byte* buffer) {
        return reinterpret_cast<const EquityAndIndexEndOfDaySummaryCategory*>(buffer);
    }
};

#pragma pack(pop)
}
