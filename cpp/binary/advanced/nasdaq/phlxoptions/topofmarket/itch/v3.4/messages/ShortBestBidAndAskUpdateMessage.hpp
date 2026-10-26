#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/OptionId.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/BidPrice2.hpp"
#include "../types/BidSize2.hpp"
#include "../types/AskPrice2.hpp"
#include "../types/AskSize2.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

namespace itch_topofmarket = ::nasdaq::phlxoptions::topofmarket::itch::v3_4;

#pragma pack(push, 1)

// Short Best Bid And Ask Update Message
struct short_best_bid_and_ask_update_message {

    struct fields_type {
        itch_topofmarket::nanoseconds nanoseconds;
        itch_topofmarket::option_id option_id;
        itch_topofmarket::quote_condition quote_condition;
        itch_topofmarket::bid_price_2 bid_price_2;
        itch_topofmarket::bid_size_2 bid_size_2;
        itch_topofmarket::ask_price_2 ask_price_2;
        itch_topofmarket::ask_size_2 ask_size_2;
    };

    itch_topofmarket::message_header header = {std::uint16_t(sizeof(itch_topofmarket::message_header) + sizeof(fields_type) - 2), message_type::enum_type::short_best_bid_and_ask_update_message};

    fields_type fields;

    // parse method
    static short_best_bid_and_ask_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<short_best_bid_and_ask_update_message*>(buffer);
    }

    // parse method const
    static const short_best_bid_and_ask_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const short_best_bid_and_ask_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(short_best_bid_and_ask_update_message::fields_type, nanoseconds) == 0, "unexpected offset of short_best_bid_and_ask_update_message::fields_type::nanoseconds");
static_assert(offsetof(short_best_bid_and_ask_update_message::fields_type, option_id) == 4, "unexpected offset of short_best_bid_and_ask_update_message::fields_type::option_id");
static_assert(offsetof(short_best_bid_and_ask_update_message::fields_type, quote_condition) == 8, "unexpected offset of short_best_bid_and_ask_update_message::fields_type::quote_condition");
static_assert(offsetof(short_best_bid_and_ask_update_message::fields_type, bid_price_2) == 9, "unexpected offset of short_best_bid_and_ask_update_message::fields_type::bid_price_2");
static_assert(offsetof(short_best_bid_and_ask_update_message::fields_type, bid_size_2) == 11, "unexpected offset of short_best_bid_and_ask_update_message::fields_type::bid_size_2");
static_assert(offsetof(short_best_bid_and_ask_update_message::fields_type, ask_price_2) == 13, "unexpected offset of short_best_bid_and_ask_update_message::fields_type::ask_price_2");
static_assert(offsetof(short_best_bid_and_ask_update_message::fields_type, ask_size_2) == 15, "unexpected offset of short_best_bid_and_ask_update_message::fields_type::ask_size_2");
static_assert(sizeof(short_best_bid_and_ask_update_message::fields_type) == 17, "unexpected sizeof short_best_bid_and_ask_update_message::fields_type");
static_assert(sizeof(short_best_bid_and_ask_update_message) == sizeof(itch_topofmarket::message_header) + 17, "unexpected sizeof short_best_bid_and_ask_update_message");

#pragma pack(pop)
}
