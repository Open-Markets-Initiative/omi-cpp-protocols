#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BuySellIndicator.hpp"
#include "../types/OptionId.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Options Trade Messages Non Auction
struct options_trade_messages_non_auction {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::buy_sell_indicator buy_sell_indicator;
        itch_itto::option_id option_id;
        itch_itto::cross_number cross_number;
        itch_itto::match_number match_number;
        itch_itto::price_long price_long;
        itch_itto::volume_long volume_long;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::options_trade_messages_non_auction};

    fields_type fields;

    // parse method
    static options_trade_messages_non_auction* parse(std::byte* buffer) {
        return reinterpret_cast<options_trade_messages_non_auction*>(buffer);
    }

    // parse method const
    static const options_trade_messages_non_auction* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_trade_messages_non_auction*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_trade_messages_non_auction::fields_type, tracking_number) == 0, "unexpected offset of options_trade_messages_non_auction::fields_type::tracking_number");
static_assert(offsetof(options_trade_messages_non_auction::fields_type, timestamp) == 2, "unexpected offset of options_trade_messages_non_auction::fields_type::timestamp");
static_assert(offsetof(options_trade_messages_non_auction::fields_type, buy_sell_indicator) == 8, "unexpected offset of options_trade_messages_non_auction::fields_type::buy_sell_indicator");
static_assert(offsetof(options_trade_messages_non_auction::fields_type, option_id) == 9, "unexpected offset of options_trade_messages_non_auction::fields_type::option_id");
static_assert(offsetof(options_trade_messages_non_auction::fields_type, cross_number) == 13, "unexpected offset of options_trade_messages_non_auction::fields_type::cross_number");
static_assert(offsetof(options_trade_messages_non_auction::fields_type, match_number) == 17, "unexpected offset of options_trade_messages_non_auction::fields_type::match_number");
static_assert(offsetof(options_trade_messages_non_auction::fields_type, price_long) == 21, "unexpected offset of options_trade_messages_non_auction::fields_type::price_long");
static_assert(offsetof(options_trade_messages_non_auction::fields_type, volume_long) == 25, "unexpected offset of options_trade_messages_non_auction::fields_type::volume_long");
static_assert(sizeof(options_trade_messages_non_auction::fields_type) == 29, "unexpected sizeof options_trade_messages_non_auction::fields_type");
static_assert(sizeof(options_trade_messages_non_auction) == sizeof(itch_itto::message_header) + 29, "unexpected sizeof options_trade_messages_non_auction");

#pragma pack(pop)
}
