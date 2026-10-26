#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/OriginalCrossId.hpp"
#include "../types/OriginalPrice.hpp"
#include "../types/OriginalVolume.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// Broken Trade Report Message
struct broken_trade_report_message {

    struct fields_type {
        itch_topofmarket::nanoseconds nanoseconds;
        itch_topofmarket::option_id option_id;
        itch_topofmarket::original_cross_id original_cross_id;
        itch_topofmarket::original_price original_price;
        itch_topofmarket::original_volume original_volume;
    };

    itch_topofmarket::message_header header = {std::uint16_t(sizeof(itch_topofmarket::message_header) + sizeof(fields_type) - 2), message_type::enum_type::broken_trade_report_message};

    fields_type fields;

    // parse method
    static broken_trade_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<broken_trade_report_message*>(buffer);
    }

    // parse method const
    static const broken_trade_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const broken_trade_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(broken_trade_report_message::fields_type, nanoseconds) == 0, "unexpected offset of broken_trade_report_message::fields_type::nanoseconds");
static_assert(offsetof(broken_trade_report_message::fields_type, option_id) == 4, "unexpected offset of broken_trade_report_message::fields_type::option_id");
static_assert(offsetof(broken_trade_report_message::fields_type, original_cross_id) == 8, "unexpected offset of broken_trade_report_message::fields_type::original_cross_id");
static_assert(offsetof(broken_trade_report_message::fields_type, original_price) == 12, "unexpected offset of broken_trade_report_message::fields_type::original_price");
static_assert(offsetof(broken_trade_report_message::fields_type, original_volume) == 16, "unexpected offset of broken_trade_report_message::fields_type::original_volume");
static_assert(sizeof(broken_trade_report_message::fields_type) == 20, "unexpected sizeof broken_trade_report_message::fields_type");
static_assert(sizeof(broken_trade_report_message) == sizeof(itch_topofmarket::message_header) + 20, "unexpected sizeof broken_trade_report_message");

#pragma pack(pop)
}
