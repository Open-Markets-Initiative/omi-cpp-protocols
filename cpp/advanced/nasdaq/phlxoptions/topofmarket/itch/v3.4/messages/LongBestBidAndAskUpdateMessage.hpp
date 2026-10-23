#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/BidPrice4.hpp"
#include "../types/BidSize4.hpp"
#include "../types/AskPrice4.hpp"
#include "../types/AskSize4.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// Long Best Bid And Ask Update Message
struct long_best_bid_and_ask_update_message {

    struct fields_type {
        itch_topofmarket::nanoseconds nanoseconds;
        itch_topofmarket::option_id option_id;
        itch_topofmarket::quote_condition quote_condition;
        itch_topofmarket::bid_price_4 bid_price_4;
        itch_topofmarket::bid_size_4 bid_size_4;
        itch_topofmarket::ask_price_4 ask_price_4;
        itch_topofmarket::ask_size_4 ask_size_4;
    };

    itch_topofmarket::message_header header = {std::uint16_t(sizeof(itch_topofmarket::message_header) + sizeof(fields_type) - 2), message_type::enum_type::long_best_bid_and_ask_update_message};

    fields_type fields;

    // parse method
    static long_best_bid_and_ask_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<long_best_bid_and_ask_update_message*>(buffer);
    }

    // parse method const
    static const long_best_bid_and_ask_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const long_best_bid_and_ask_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(long_best_bid_and_ask_update_message::fields_type, nanoseconds) == 0, "unexpected offset of long_best_bid_and_ask_update_message::fields_type::nanoseconds");
static_assert(offsetof(long_best_bid_and_ask_update_message::fields_type, option_id) == 4, "unexpected offset of long_best_bid_and_ask_update_message::fields_type::option_id");
static_assert(offsetof(long_best_bid_and_ask_update_message::fields_type, quote_condition) == 8, "unexpected offset of long_best_bid_and_ask_update_message::fields_type::quote_condition");
static_assert(offsetof(long_best_bid_and_ask_update_message::fields_type, bid_price_4) == 9, "unexpected offset of long_best_bid_and_ask_update_message::fields_type::bid_price_4");
static_assert(offsetof(long_best_bid_and_ask_update_message::fields_type, bid_size_4) == 13, "unexpected offset of long_best_bid_and_ask_update_message::fields_type::bid_size_4");
static_assert(offsetof(long_best_bid_and_ask_update_message::fields_type, ask_price_4) == 17, "unexpected offset of long_best_bid_and_ask_update_message::fields_type::ask_price_4");
static_assert(offsetof(long_best_bid_and_ask_update_message::fields_type, ask_size_4) == 21, "unexpected offset of long_best_bid_and_ask_update_message::fields_type::ask_size_4");
static_assert(sizeof(long_best_bid_and_ask_update_message::fields_type) == 25, "unexpected sizeof long_best_bid_and_ask_update_message::fields_type");
static_assert(sizeof(long_best_bid_and_ask_update_message) == sizeof(itch_topofmarket::message_header) + 25, "unexpected sizeof long_best_bid_and_ask_update_message");

#pragma pack(pop)
}
