#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/AuctionId.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/PriceLong.hpp"
#include "../types/Contracts.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Auction Trade Message
struct auction_trade_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::auction_id auction_id;
        pitch_multicastdepthofbook::execution_id execution_id;
        pitch_multicastdepthofbook::price_long price_long;
        pitch_multicastdepthofbook::contracts contracts;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::auction_trade_message};

    fields_type fields;

    // parse method
    static auction_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_trade_message*>(buffer);
    }

    // parse method const
    static const auction_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_trade_message::fields_type, time_offset) == 0, "unexpected offset of auction_trade_message::fields_type::time_offset");
static_assert(offsetof(auction_trade_message::fields_type, auction_id) == 4, "unexpected offset of auction_trade_message::fields_type::auction_id");
static_assert(offsetof(auction_trade_message::fields_type, execution_id) == 12, "unexpected offset of auction_trade_message::fields_type::execution_id");
static_assert(offsetof(auction_trade_message::fields_type, price_long) == 20, "unexpected offset of auction_trade_message::fields_type::price_long");
static_assert(offsetof(auction_trade_message::fields_type, contracts) == 28, "unexpected offset of auction_trade_message::fields_type::contracts");
static_assert(sizeof(auction_trade_message::fields_type) == 32, "unexpected sizeof auction_trade_message::fields_type");
static_assert(sizeof(auction_trade_message) == sizeof(pitch_multicastdepthofbook::message_header) + 32, "unexpected sizeof auction_trade_message");

#pragma pack(pop)
}
