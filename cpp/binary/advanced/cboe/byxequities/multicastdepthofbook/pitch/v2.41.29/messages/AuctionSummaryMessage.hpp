#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/AuctionOpeningType.hpp"
#include "../types/Price.hpp"
#include "../types/SharesContracts.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

namespace pitch_multicastdepthofbook = ::cboe::byxequities::multicastdepthofbook::pitch::v2_41_29;

#pragma pack(push, 1)

// Auction Summary Message
struct auction_summary_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol_long symbol_long;
        pitch_multicastdepthofbook::auction_opening_type auction_opening_type;
        pitch_multicastdepthofbook::price price;
        pitch_multicastdepthofbook::shares_contracts shares_contracts;
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
static_assert(offsetof(auction_summary_message::fields_type, symbol_long) == 4, "unexpected offset of auction_summary_message::fields_type::symbol_long");
static_assert(offsetof(auction_summary_message::fields_type, auction_opening_type) == 12, "unexpected offset of auction_summary_message::fields_type::auction_opening_type");
static_assert(offsetof(auction_summary_message::fields_type, price) == 13, "unexpected offset of auction_summary_message::fields_type::price");
static_assert(offsetof(auction_summary_message::fields_type, shares_contracts) == 21, "unexpected offset of auction_summary_message::fields_type::shares_contracts");
static_assert(sizeof(auction_summary_message::fields_type) == 25, "unexpected sizeof auction_summary_message::fields_type");
static_assert(sizeof(auction_summary_message) == sizeof(pitch_multicastdepthofbook::message_header) + 25, "unexpected sizeof auction_summary_message");

#pragma pack(pop)
}
