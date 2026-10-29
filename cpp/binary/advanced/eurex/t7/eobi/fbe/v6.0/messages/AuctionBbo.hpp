#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/BidPx.hpp"
#include "../types/OfferPx.hpp"
#include "../types/BidSize.hpp"
#include "../types/OfferSize.hpp"
#include "../types/PotentialSecurityTradingEvent.hpp"
#include "../types/Pad7.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v6_0;

#pragma pack(push, 1)

// Auction Bbo
struct auction_bbo {

    struct fields_type {
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::bid_px bid_px;
        fbe_eobi::offer_px offer_px;
        fbe_eobi::bid_size bid_size;
        fbe_eobi::offer_size offer_size;
        fbe_eobi::potential_security_trading_event potential_security_trading_event;
        fbe_eobi::pad7 pad7;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::auction_bbo, {}};

    fields_type fields;

    // parse method
    static auction_bbo* parse(std::byte* buffer) {
        return reinterpret_cast<auction_bbo*>(buffer);
    }

    // parse method const
    static const auction_bbo* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_bbo*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_bbo::fields_type, transact_time) == 0, "unexpected offset of auction_bbo::fields_type::transact_time");
static_assert(offsetof(auction_bbo::fields_type, security_id) == 8, "unexpected offset of auction_bbo::fields_type::security_id");
static_assert(offsetof(auction_bbo::fields_type, bid_px) == 16, "unexpected offset of auction_bbo::fields_type::bid_px");
static_assert(offsetof(auction_bbo::fields_type, offer_px) == 24, "unexpected offset of auction_bbo::fields_type::offer_px");
static_assert(offsetof(auction_bbo::fields_type, bid_size) == 32, "unexpected offset of auction_bbo::fields_type::bid_size");
static_assert(offsetof(auction_bbo::fields_type, offer_size) == 36, "unexpected offset of auction_bbo::fields_type::offer_size");
static_assert(offsetof(auction_bbo::fields_type, potential_security_trading_event) == 40, "unexpected offset of auction_bbo::fields_type::potential_security_trading_event");
static_assert(offsetof(auction_bbo::fields_type, pad7) == 41, "unexpected offset of auction_bbo::fields_type::pad7");
static_assert(sizeof(auction_bbo::fields_type) == 48, "unexpected sizeof auction_bbo::fields_type");
static_assert(sizeof(auction_bbo) == sizeof(fbe_eobi::message_header_comp) + 48, "unexpected sizeof auction_bbo");

#pragma pack(pop)
}
