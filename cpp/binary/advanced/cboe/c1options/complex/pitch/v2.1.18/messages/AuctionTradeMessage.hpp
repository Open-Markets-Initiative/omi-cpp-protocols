#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/AuctionId.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Price.hpp"
#include "../types/Quantity.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Auction Trade Message
struct auction_trade_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::auction_id auction_id;
        pitch_complex::execution_id execution_id;
        pitch_complex::price price;
        pitch_complex::quantity quantity;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::auction_trade_message};

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
static_assert(offsetof(auction_trade_message::fields_type, price) == 20, "unexpected offset of auction_trade_message::fields_type::price");
static_assert(offsetof(auction_trade_message::fields_type, quantity) == 28, "unexpected offset of auction_trade_message::fields_type::quantity");
static_assert(sizeof(auction_trade_message::fields_type) == 32, "unexpected sizeof auction_trade_message::fields_type");
static_assert(sizeof(auction_trade_message) == sizeof(pitch_complex::message_header) + 32, "unexpected sizeof auction_trade_message");

#pragma pack(pop)
}
