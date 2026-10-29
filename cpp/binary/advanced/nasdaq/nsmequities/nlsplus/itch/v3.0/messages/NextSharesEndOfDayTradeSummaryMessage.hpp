#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/IssueSymbol.hpp"
#include "../types/MarketCategory.hpp"
#include "../types/ConsolidatedHighPrice.hpp"
#include "../types/NavOffsetAmountHigh.hpp"
#include "../types/ConsolidatedLowPrice.hpp"
#include "../types/NavOffsetAmountLow.hpp"
#include "../types/ConsolidatedClosingPrice.hpp"
#include "../types/NavOffsetAmountClosing.hpp"
#include "../types/ConsolidatedVolume.hpp"
#include "../types/ConsolidatedOpenPrice.hpp"
#include "../types/NavOffsetAmountOpen.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

// Next Shares End Of Day Trade Summary Message
struct next_shares_end_of_day_trade_summary_message {

    struct fields_type {
        itch_nlsplus::issue_symbol issue_symbol;
        itch_nlsplus::market_category market_category;
        itch_nlsplus::consolidated_high_price consolidated_high_price;
        itch_nlsplus::nav_offset_amount_high nav_offset_amount_high;
        itch_nlsplus::consolidated_low_price consolidated_low_price;
        itch_nlsplus::nav_offset_amount_low nav_offset_amount_low;
        itch_nlsplus::consolidated_closing_price consolidated_closing_price;
        itch_nlsplus::nav_offset_amount_closing nav_offset_amount_closing;
        itch_nlsplus::consolidated_volume consolidated_volume;
        itch_nlsplus::consolidated_open_price consolidated_open_price;
        itch_nlsplus::nav_offset_amount_open nav_offset_amount_open;
    };

    itch_nlsplus::message_header header = {std::uint16_t(sizeof(itch_nlsplus::message_header) + sizeof(fields_type) - 2), {}, {}, message_type::enum_type::next_shares_end_of_day_trade_summary_message};

    fields_type fields;

    // parse method
    static next_shares_end_of_day_trade_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<next_shares_end_of_day_trade_summary_message*>(buffer);
    }

    // parse method const
    static const next_shares_end_of_day_trade_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const next_shares_end_of_day_trade_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, issue_symbol) == 0, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::issue_symbol");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, market_category) == 8, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::market_category");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, consolidated_high_price) == 9, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::consolidated_high_price");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, nav_offset_amount_high) == 13, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::nav_offset_amount_high");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, consolidated_low_price) == 17, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::consolidated_low_price");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, nav_offset_amount_low) == 21, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::nav_offset_amount_low");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, consolidated_closing_price) == 25, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::consolidated_closing_price");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, nav_offset_amount_closing) == 29, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::nav_offset_amount_closing");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, consolidated_volume) == 33, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::consolidated_volume");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, consolidated_open_price) == 41, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::consolidated_open_price");
static_assert(offsetof(next_shares_end_of_day_trade_summary_message::fields_type, nav_offset_amount_open) == 45, "unexpected offset of next_shares_end_of_day_trade_summary_message::fields_type::nav_offset_amount_open");
static_assert(sizeof(next_shares_end_of_day_trade_summary_message::fields_type) == 49, "unexpected sizeof next_shares_end_of_day_trade_summary_message::fields_type");
static_assert(sizeof(next_shares_end_of_day_trade_summary_message) == sizeof(itch_nlsplus::message_header) + 49, "unexpected sizeof next_shares_end_of_day_trade_summary_message");

#pragma pack(pop)
}
