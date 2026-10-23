#pragma once

#include "../types/ShortEquityAndIndexQuoteMessageType.hpp"

namespace siac::opra::output::obi::v6_2 {

#pragma pack(push, 1)

struct ShortEquityAndIndexQuoteCategory {

    ShortEquityAndIndexQuoteMessageType short_equity_and_index_quote_message_type;

    // parse method
    static ShortEquityAndIndexQuoteCategory* parse(std::byte* buffer) {
        return reinterpret_cast<ShortEquityAndIndexQuoteCategory*>(buffer);
    }

    // parse method const
    static const ShortEquityAndIndexQuoteCategory* parse(const std::byte* buffer) {
        return reinterpret_cast<const ShortEquityAndIndexQuoteCategory*>(buffer);
    }
};

#pragma pack(pop)
}
