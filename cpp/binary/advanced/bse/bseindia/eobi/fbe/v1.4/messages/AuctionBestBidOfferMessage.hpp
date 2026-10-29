#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/BidPx.hpp"
#include "../types/OfferPx.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Auction Best Bid Offer Message
struct auction_best_bid_offer_message {

    struct fields_type {
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::bid_px bid_px;
        fbe_eobi::offer_px offer_px;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::auction_best_bid_offer_message, {}};

    fields_type fields;

    // parse method
    static auction_best_bid_offer_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_best_bid_offer_message*>(buffer);
    }

    // parse method const
    static const auction_best_bid_offer_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_best_bid_offer_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_best_bid_offer_message::fields_type, transact_time) == 0, "unexpected offset of auction_best_bid_offer_message::fields_type::transact_time");
static_assert(offsetof(auction_best_bid_offer_message::fields_type, security_id) == 8, "unexpected offset of auction_best_bid_offer_message::fields_type::security_id");
static_assert(offsetof(auction_best_bid_offer_message::fields_type, bid_px) == 16, "unexpected offset of auction_best_bid_offer_message::fields_type::bid_px");
static_assert(offsetof(auction_best_bid_offer_message::fields_type, offer_px) == 24, "unexpected offset of auction_best_bid_offer_message::fields_type::offer_px");
static_assert(sizeof(auction_best_bid_offer_message::fields_type) == 32, "unexpected sizeof auction_best_bid_offer_message::fields_type");
static_assert(sizeof(auction_best_bid_offer_message) == sizeof(fbe_eobi::message_header) + 32, "unexpected sizeof auction_best_bid_offer_message");

#pragma pack(pop)
}
