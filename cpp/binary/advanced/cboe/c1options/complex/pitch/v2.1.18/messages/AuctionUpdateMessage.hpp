#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/ComplexInstrumentId8.hpp"
#include "../types/AuctionOpeningType.hpp"
#include "../types/ReferencePrice.hpp"
#include "../types/BuyContracts.hpp"
#include "../types/SellContracts.hpp"
#include "../types/IndicativePrice.hpp"
#include "../types/AuctionOnlyPrice.hpp"
#include "../types/OpeningCondition.hpp"
#include "../types/CompositeMarketBidPrice.hpp"
#include "../types/CompositeMarketOfferPrice.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Auction Update Message
struct auction_update_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::complex_instrument_id_8 complex_instrument_id_8;
        pitch_complex::auction_opening_type auction_opening_type;
        pitch_complex::reference_price reference_price;
        pitch_complex::buy_contracts buy_contracts;
        pitch_complex::sell_contracts sell_contracts;
        pitch_complex::indicative_price indicative_price;
        pitch_complex::auction_only_price auction_only_price;
        pitch_complex::opening_condition opening_condition;
        pitch_complex::composite_market_bid_price composite_market_bid_price;
        pitch_complex::composite_market_offer_price composite_market_offer_price;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::auction_update_message};

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
static_assert(offsetof(auction_update_message::fields_type, complex_instrument_id_8) == 4, "unexpected offset of auction_update_message::fields_type::complex_instrument_id_8");
static_assert(offsetof(auction_update_message::fields_type, auction_opening_type) == 12, "unexpected offset of auction_update_message::fields_type::auction_opening_type");
static_assert(offsetof(auction_update_message::fields_type, reference_price) == 13, "unexpected offset of auction_update_message::fields_type::reference_price");
static_assert(offsetof(auction_update_message::fields_type, buy_contracts) == 21, "unexpected offset of auction_update_message::fields_type::buy_contracts");
static_assert(offsetof(auction_update_message::fields_type, sell_contracts) == 25, "unexpected offset of auction_update_message::fields_type::sell_contracts");
static_assert(offsetof(auction_update_message::fields_type, indicative_price) == 29, "unexpected offset of auction_update_message::fields_type::indicative_price");
static_assert(offsetof(auction_update_message::fields_type, auction_only_price) == 37, "unexpected offset of auction_update_message::fields_type::auction_only_price");
static_assert(offsetof(auction_update_message::fields_type, opening_condition) == 45, "unexpected offset of auction_update_message::fields_type::opening_condition");
static_assert(offsetof(auction_update_message::fields_type, composite_market_bid_price) == 46, "unexpected offset of auction_update_message::fields_type::composite_market_bid_price");
static_assert(offsetof(auction_update_message::fields_type, composite_market_offer_price) == 54, "unexpected offset of auction_update_message::fields_type::composite_market_offer_price");
static_assert(sizeof(auction_update_message::fields_type) == 62, "unexpected sizeof auction_update_message::fields_type");
static_assert(sizeof(auction_update_message) == sizeof(pitch_complex::message_header) + 62, "unexpected sizeof auction_update_message");

#pragma pack(pop)
}
