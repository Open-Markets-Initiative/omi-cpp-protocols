#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/CrossId.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Price4.hpp"
#include "../types/Volume.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// Trade Report Message
struct trade_report_message {

    struct fields_type {
        itch_topofmarket::nanoseconds nanoseconds;
        itch_topofmarket::option_id option_id;
        itch_topofmarket::cross_id cross_id;
        itch_topofmarket::trade_condition trade_condition;
        itch_topofmarket::price_4 price_4;
        itch_topofmarket::volume volume;
    };

    itch_topofmarket::message_header header = {std::uint16_t(sizeof(itch_topofmarket::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_report_message};

    fields_type fields;

    // parse method
    static trade_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_report_message*>(buffer);
    }

    // parse method const
    static const trade_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_report_message::fields_type, nanoseconds) == 0, "unexpected offset of trade_report_message::fields_type::nanoseconds");
static_assert(offsetof(trade_report_message::fields_type, option_id) == 4, "unexpected offset of trade_report_message::fields_type::option_id");
static_assert(offsetof(trade_report_message::fields_type, cross_id) == 8, "unexpected offset of trade_report_message::fields_type::cross_id");
static_assert(offsetof(trade_report_message::fields_type, trade_condition) == 12, "unexpected offset of trade_report_message::fields_type::trade_condition");
static_assert(offsetof(trade_report_message::fields_type, price_4) == 13, "unexpected offset of trade_report_message::fields_type::price_4");
static_assert(offsetof(trade_report_message::fields_type, volume) == 17, "unexpected offset of trade_report_message::fields_type::volume");
static_assert(sizeof(trade_report_message::fields_type) == 21, "unexpected sizeof trade_report_message::fields_type");
static_assert(sizeof(trade_report_message) == sizeof(itch_topofmarket::message_header) + 21, "unexpected sizeof trade_report_message");

#pragma pack(pop)
}
