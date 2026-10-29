#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/ConsolidatedHighPrice.hpp"
#include "../types/ConsolidatedLowPrice.hpp"
#include "../types/ConsolidatedClosingPrice.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../types/ConsolidatedOpenPrice.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// End Of Day Trade Summary Message
struct end_of_day_trade_summary_message {

    struct fields_type {
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::market_category market_category;
        itch_nlsplus::consolidated_high_price consolidated_high_price;
        itch_nlsplus::consolidated_low_price consolidated_low_price;
        itch_nlsplus::consolidated_closing_price consolidated_closing_price;
        itch_nlsplus::consolidated_volume consolidated_volume;
        itch_nlsplus::consolidated_open_price consolidated_open_price;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::end_of_day_trade_summary_message};

    fields_type fields;

    // parse method
    static end_of_day_trade_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<end_of_day_trade_summary_message*>(buffer);
    }

    // parse method const
    static const end_of_day_trade_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const end_of_day_trade_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(end_of_day_trade_summary_message::fields_type, issue_symbol) == 0, "unexpected offset of end_of_day_trade_summary_message::fields_type::issue_symbol");
static_assert(offsetof(end_of_day_trade_summary_message::fields_type, market_category) == 8, "unexpected offset of end_of_day_trade_summary_message::fields_type::market_category");
static_assert(offsetof(end_of_day_trade_summary_message::fields_type, consolidated_high_price) == 9, "unexpected offset of end_of_day_trade_summary_message::fields_type::consolidated_high_price");
static_assert(offsetof(end_of_day_trade_summary_message::fields_type, consolidated_low_price) == 13, "unexpected offset of end_of_day_trade_summary_message::fields_type::consolidated_low_price");
static_assert(offsetof(end_of_day_trade_summary_message::fields_type, consolidated_closing_price) == 17, "unexpected offset of end_of_day_trade_summary_message::fields_type::consolidated_closing_price");
static_assert(offsetof(end_of_day_trade_summary_message::fields_type, consolidated_volume) == 21, "unexpected offset of end_of_day_trade_summary_message::fields_type::consolidated_volume");
static_assert(offsetof(end_of_day_trade_summary_message::fields_type, consolidated_open_price) == 29, "unexpected offset of end_of_day_trade_summary_message::fields_type::consolidated_open_price");
static_assert(sizeof(end_of_day_trade_summary_message::fields_type) == 33, "unexpected sizeof end_of_day_trade_summary_message::fields_type");
static_assert(sizeof(end_of_day_trade_summary_message) == sizeof(itch_nlsplus::message_header) + 33, "unexpected sizeof end_of_day_trade_summary_message");

#pragma pack(pop)
}
