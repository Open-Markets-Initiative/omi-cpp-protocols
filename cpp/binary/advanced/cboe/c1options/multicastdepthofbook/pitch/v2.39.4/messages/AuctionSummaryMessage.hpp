#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/StockSymbol.hpp"
#include "../types/AuctionType.hpp"
#include "../types/LongPrice.hpp"
#include "../types/Shares.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// Auction Summary Message
struct auction_summary_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::stock_symbol stock_symbol;
        pitch_multicastdepthofbook::auction_type auction_type;
        pitch_multicastdepthofbook::long_price long_price;
        pitch_multicastdepthofbook::shares shares;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::auction_summary_message};

    fields_type fields;

    // parse method
    static auction_summary_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_summary_message*>(buffer);
    }

    // parse method const
    static const auction_summary_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_summary_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_summary_message::fields_type, time_offset) == 0, "unexpected offset of auction_summary_message::fields_type::time_offset");
static_assert(offsetof(auction_summary_message::fields_type, stock_symbol) == 4, "unexpected offset of auction_summary_message::fields_type::stock_symbol");
static_assert(offsetof(auction_summary_message::fields_type, auction_type) == 12, "unexpected offset of auction_summary_message::fields_type::auction_type");
static_assert(offsetof(auction_summary_message::fields_type, long_price) == 13, "unexpected offset of auction_summary_message::fields_type::long_price");
static_assert(offsetof(auction_summary_message::fields_type, shares) == 21, "unexpected offset of auction_summary_message::fields_type::shares");
static_assert(sizeof(auction_summary_message::fields_type) == 25, "unexpected sizeof auction_summary_message::fields_type");
static_assert(sizeof(auction_summary_message) == sizeof(pitch_multicastdepthofbook::message_header) + 25, "unexpected sizeof auction_summary_message");

#pragma pack(pop)
}
