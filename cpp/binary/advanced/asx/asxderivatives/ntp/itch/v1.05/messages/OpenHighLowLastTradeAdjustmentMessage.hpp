#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/OpeningTrade.hpp"
#include "../types/HighestTrade.hpp"
#include "../types/LowestTrade.hpp"
#include "../types/LastTrade.hpp"
#include "../types/LastVolume.hpp"
#include "../types/TotalTradedVolume.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Open High Low Last Trade Adjustment Message
struct open_high_low_last_trade_adjustment_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::tradeable_instrument_id tradeable_instrument_id;
        itch_ntp::opening_trade opening_trade;
        itch_ntp::highest_trade highest_trade;
        itch_ntp::lowest_trade lowest_trade;
        itch_ntp::last_trade last_trade;
        itch_ntp::last_volume last_volume;
        itch_ntp::total_traded_volume total_traded_volume;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::open_high_low_last_trade_adjustment_message};

    fields_type fields;

    // parse method
    static open_high_low_last_trade_adjustment_message* parse(std::byte* buffer) {
        return reinterpret_cast<open_high_low_last_trade_adjustment_message*>(buffer);
    }

    // parse method const
    static const open_high_low_last_trade_adjustment_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const open_high_low_last_trade_adjustment_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, nanoseconds) == 0, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::nanoseconds");
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, trade_date) == 4, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::trade_date");
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, tradeable_instrument_id) == 6, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::tradeable_instrument_id");
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, opening_trade) == 10, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::opening_trade");
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, highest_trade) == 18, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::highest_trade");
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, lowest_trade) == 26, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::lowest_trade");
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, last_trade) == 34, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::last_trade");
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, last_volume) == 42, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::last_volume");
static_assert(offsetof(open_high_low_last_trade_adjustment_message::fields_type, total_traded_volume) == 46, "unexpected offset of open_high_low_last_trade_adjustment_message::fields_type::total_traded_volume");
static_assert(sizeof(open_high_low_last_trade_adjustment_message::fields_type) == 54, "unexpected sizeof open_high_low_last_trade_adjustment_message::fields_type");
static_assert(sizeof(open_high_low_last_trade_adjustment_message) == sizeof(itch_ntp::message_header) + 54, "unexpected sizeof open_high_low_last_trade_adjustment_message");

#pragma pack(pop)
}
