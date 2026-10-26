#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OptionId.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/CrossType.hpp"
#include "../types/PriceLong.hpp"
#include "../types/VolumeLong.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Options Cross Trade Message
struct options_cross_trade_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::option_id option_id;
        itch_itto::cross_number cross_number;
        itch_itto::match_number match_number;
        itch_itto::cross_type cross_type;
        itch_itto::price_long price_long;
        itch_itto::volume_long volume_long;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::options_cross_trade_message};

    fields_type fields;

    // parse method
    static options_cross_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_cross_trade_message*>(buffer);
    }

    // parse method const
    static const options_cross_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_cross_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_cross_trade_message::fields_type, tracking_number) == 0, "unexpected offset of options_cross_trade_message::fields_type::tracking_number");
static_assert(offsetof(options_cross_trade_message::fields_type, timestamp) == 2, "unexpected offset of options_cross_trade_message::fields_type::timestamp");
static_assert(offsetof(options_cross_trade_message::fields_type, option_id) == 8, "unexpected offset of options_cross_trade_message::fields_type::option_id");
static_assert(offsetof(options_cross_trade_message::fields_type, cross_number) == 12, "unexpected offset of options_cross_trade_message::fields_type::cross_number");
static_assert(offsetof(options_cross_trade_message::fields_type, match_number) == 16, "unexpected offset of options_cross_trade_message::fields_type::match_number");
static_assert(offsetof(options_cross_trade_message::fields_type, cross_type) == 20, "unexpected offset of options_cross_trade_message::fields_type::cross_type");
static_assert(offsetof(options_cross_trade_message::fields_type, price_long) == 21, "unexpected offset of options_cross_trade_message::fields_type::price_long");
static_assert(offsetof(options_cross_trade_message::fields_type, volume_long) == 25, "unexpected offset of options_cross_trade_message::fields_type::volume_long");
static_assert(sizeof(options_cross_trade_message::fields_type) == 29, "unexpected sizeof options_cross_trade_message::fields_type");
static_assert(sizeof(options_cross_trade_message) == sizeof(itch_itto::message_header) + 29, "unexpected sizeof options_cross_trade_message");

#pragma pack(pop)
}
