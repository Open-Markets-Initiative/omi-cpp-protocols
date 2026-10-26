#pragma once

#include "../types/LongEquityAndIndexQuoteMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct LongEquityAndIndexQuoteCategory {

    LongEquityAndIndexQuoteMessageType long_equity_and_index_quote_message_type;

    // parse method
    static LongEquityAndIndexQuoteCategory* parse(std::byte* buffer) {
        return reinterpret_cast<LongEquityAndIndexQuoteCategory*>(buffer);
    }

    // parse method const
    static const LongEquityAndIndexQuoteCategory* parse(const std::byte* buffer) {
        return reinterpret_cast<const LongEquityAndIndexQuoteCategory*>(buffer);
    }
};

#pragma pack(pop)
}
