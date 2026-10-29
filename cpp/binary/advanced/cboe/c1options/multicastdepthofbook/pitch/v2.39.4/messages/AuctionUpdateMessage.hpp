#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/StockSymbol.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/BuyShares.hpp"
#include "../types/SellShares.hpp"
#include "../types/IndicativePrice.hpp"
#include "../types/AuctionOnlyPrice.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// Auction Update Message
struct auction_update_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::stock_symbol stock_symbol;
        pitch_multicastdepthofbook::auction_type auction_type;
        pitch_multicastdepthofbook::reference_price reference_price;
        pitch_multicastdepthofbook::buy_shares buy_shares;
        pitch_multicastdepthofbook::sell_shares sell_shares;
        pitch_multicastdepthofbook::indicative_price indicative_price;
        pitch_multicastdepthofbook::auction_only_price auction_only_price;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::auction_update_message};

    fields_type fields;

    // parse method
    static auction_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_update_message*>(buffer);
    }

    // parse method const
    static const auction_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_update_message::fields_type, time_offset) == 0, "unexpected offset of auction_update_message::fields_type::time_offset");
static_assert(offsetof(auction_update_message::fields_type, stock_symbol) == 4, "unexpected offset of auction_update_message::fields_type::stock_symbol");
static_assert(offsetof(auction_update_message::fields_type, auction_type) == 12, "unexpected offset of auction_update_message::fields_type::auction_type");
static_assert(offsetof(auction_update_message::fields_type, reference_price) == 13, "unexpected offset of auction_update_message::fields_type::reference_price");
static_assert(offsetof(auction_update_message::fields_type, buy_shares) == 21, "unexpected offset of auction_update_message::fields_type::buy_shares");
static_assert(offsetof(auction_update_message::fields_type, sell_shares) == 25, "unexpected offset of auction_update_message::fields_type::sell_shares");
static_assert(offsetof(auction_update_message::fields_type, indicative_price) == 29, "unexpected offset of auction_update_message::fields_type::indicative_price");
static_assert(offsetof(auction_update_message::fields_type, auction_only_price) == 37, "unexpected offset of auction_update_message::fields_type::auction_only_price");
static_assert(sizeof(auction_update_message::fields_type) == 45, "unexpected sizeof auction_update_message::fields_type");
static_assert(sizeof(auction_update_message) == sizeof(pitch_multicastdepthofbook::message_header) + 45, "unexpected sizeof auction_update_message");

#pragma pack(pop)
}
