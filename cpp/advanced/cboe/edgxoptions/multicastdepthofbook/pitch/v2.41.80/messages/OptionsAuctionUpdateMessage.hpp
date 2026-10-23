#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/ExpandedSymbol.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/BuyContracts.hpp"
#include "../types/SellContracts.hpp"
#include "../types/IndicativePrice.hpp"
#include "../types/AuctionOnlyPrice.hpp"
#include "../types/OpeningCondition.hpp"
#include "../types/CompositeMarketBidPrice.hpp"
#include "../types/CompositeMarketOfferPrice.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Options Auction Update Message
struct options_auction_update_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::expanded_symbol expanded_symbol;
        pitch_multicastdepthofbook::auction_type auction_type;
        pitch_multicastdepthofbook::reference_price reference_price;
        pitch_multicastdepthofbook::buy_contracts buy_contracts;
        pitch_multicastdepthofbook::sell_contracts sell_contracts;
        pitch_multicastdepthofbook::indicative_price indicative_price;
        pitch_multicastdepthofbook::auction_only_price auction_only_price;
        pitch_multicastdepthofbook::opening_condition opening_condition;
        pitch_multicastdepthofbook::composite_market_bid_price composite_market_bid_price;
        pitch_multicastdepthofbook::composite_market_offer_price composite_market_offer_price;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::options_auction_update_message};

    fields_type fields;

    // parse method
    static options_auction_update_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_auction_update_message*>(buffer);
    }

    // parse method const
    static const options_auction_update_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_auction_update_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_auction_update_message::fields_type, time_offset) == 0, "unexpected offset of options_auction_update_message::fields_type::time_offset");
static_assert(offsetof(options_auction_update_message::fields_type, expanded_symbol) == 4, "unexpected offset of options_auction_update_message::fields_type::expanded_symbol");
static_assert(offsetof(options_auction_update_message::fields_type, auction_type) == 12, "unexpected offset of options_auction_update_message::fields_type::auction_type");
static_assert(offsetof(options_auction_update_message::fields_type, reference_price) == 13, "unexpected offset of options_auction_update_message::fields_type::reference_price");
static_assert(offsetof(options_auction_update_message::fields_type, buy_contracts) == 21, "unexpected offset of options_auction_update_message::fields_type::buy_contracts");
static_assert(offsetof(options_auction_update_message::fields_type, sell_contracts) == 25, "unexpected offset of options_auction_update_message::fields_type::sell_contracts");
static_assert(offsetof(options_auction_update_message::fields_type, indicative_price) == 29, "unexpected offset of options_auction_update_message::fields_type::indicative_price");
static_assert(offsetof(options_auction_update_message::fields_type, auction_only_price) == 37, "unexpected offset of options_auction_update_message::fields_type::auction_only_price");
static_assert(offsetof(options_auction_update_message::fields_type, opening_condition) == 45, "unexpected offset of options_auction_update_message::fields_type::opening_condition");
static_assert(offsetof(options_auction_update_message::fields_type, composite_market_bid_price) == 46, "unexpected offset of options_auction_update_message::fields_type::composite_market_bid_price");
static_assert(offsetof(options_auction_update_message::fields_type, composite_market_offer_price) == 54, "unexpected offset of options_auction_update_message::fields_type::composite_market_offer_price");
static_assert(sizeof(options_auction_update_message::fields_type) == 62, "unexpected sizeof options_auction_update_message::fields_type");
static_assert(sizeof(options_auction_update_message) == sizeof(pitch_multicastdepthofbook::message_header) + 62, "unexpected sizeof options_auction_update_message");

#pragma pack(pop)
}
