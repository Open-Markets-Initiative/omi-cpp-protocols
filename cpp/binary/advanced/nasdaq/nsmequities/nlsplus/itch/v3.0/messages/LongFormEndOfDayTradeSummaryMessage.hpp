#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/ConsolidatedHighPriceLong.hpp"
#include "../types/ConsolidatedLowPriceLong.hpp"
#include "../types/ConsolidatedClosingPriceLong.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../types/ConsolidatedOpenPriceLong.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Long Form End Of Day Trade Summary Message
struct long_form_end_of_day_trade_summary_message {

    struct fields_type {
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::market_category market_category;
        itch_nlsplus::consolidated_high_price_long consolidated_high_price_long;
        itch_nlsplus::consolidated_low_price_long consolidated_low_price_long;
        itch_nlsplus::consolidated_closing_price_long consolidated_closing_price_long;
        itch_nlsplus::consolidated_volume consolidated_volume;
        itch_nlsplus::consolidated_open_price_long consolidated_open_price_long;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::long_form_end_of_day_trade_summary_message};

    fields_type fields;

    // parse method
    static long_form_end_of_day_trade_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<long_form_end_of_day_trade_summary_message*>(buffer);
    }

    // parse method const
    static const long_form_end_of_day_trade_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const long_form_end_of_day_trade_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(long_form_end_of_day_trade_summary_message::fields_type, issue_symbol) == 0, "unexpected offset of long_form_end_of_day_trade_summary_message::fields_type::issue_symbol");
static_assert(offsetof(long_form_end_of_day_trade_summary_message::fields_type, market_category) == 8, "unexpected offset of long_form_end_of_day_trade_summary_message::fields_type::market_category");
static_assert(offsetof(long_form_end_of_day_trade_summary_message::fields_type, consolidated_high_price_long) == 9, "unexpected offset of long_form_end_of_day_trade_summary_message::fields_type::consolidated_high_price_long");
static_assert(offsetof(long_form_end_of_day_trade_summary_message::fields_type, consolidated_low_price_long) == 17, "unexpected offset of long_form_end_of_day_trade_summary_message::fields_type::consolidated_low_price_long");
static_assert(offsetof(long_form_end_of_day_trade_summary_message::fields_type, consolidated_closing_price_long) == 25, "unexpected offset of long_form_end_of_day_trade_summary_message::fields_type::consolidated_closing_price_long");
static_assert(offsetof(long_form_end_of_day_trade_summary_message::fields_type, consolidated_volume) == 33, "unexpected offset of long_form_end_of_day_trade_summary_message::fields_type::consolidated_volume");
static_assert(offsetof(long_form_end_of_day_trade_summary_message::fields_type, consolidated_open_price_long) == 41, "unexpected offset of long_form_end_of_day_trade_summary_message::fields_type::consolidated_open_price_long");
static_assert(sizeof(long_form_end_of_day_trade_summary_message::fields_type) == 49, "unexpected sizeof long_form_end_of_day_trade_summary_message::fields_type");
static_assert(sizeof(long_form_end_of_day_trade_summary_message) == sizeof(itch_nlsplus::message_header) + 49, "unexpected sizeof long_form_end_of_day_trade_summary_message");

#pragma pack(pop)
}
