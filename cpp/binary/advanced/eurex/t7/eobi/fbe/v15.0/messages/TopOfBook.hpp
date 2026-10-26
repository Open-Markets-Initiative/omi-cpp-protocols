#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/BidPx.hpp"
#include "../types/OfferPx.hpp"
#include "../types/BidSize.hpp"
#include "../types/OfferSize.hpp"
#include "../types/NumberOfBuyOrders.hpp"
#include "../types/NumberOfSellOrders.hpp"
#include "../types/Pad4.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Top Of Book
struct top_of_book {

    struct fields_type {
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::bid_px bid_px;
        fbe_eobi::offer_px offer_px;
        fbe_eobi::bid_size bid_size;
        fbe_eobi::offer_size offer_size;
        fbe_eobi::number_of_buy_orders number_of_buy_orders;
        fbe_eobi::number_of_sell_orders number_of_sell_orders;
        fbe_eobi::pad4 pad4;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::top_of_book, {}};

    fields_type fields;

    // parse method
    static top_of_book* parse(std::byte* buffer) {
        return reinterpret_cast<top_of_book*>(buffer);
    }

    // parse method const
    static const top_of_book* parse(const std::byte* buffer) {
        return reinterpret_cast<const top_of_book*>(buffer);
    }

};

// layout verification
static_assert(offsetof(top_of_book::fields_type, transact_time) == 0, "unexpected offset of top_of_book::fields_type::transact_time");
static_assert(offsetof(top_of_book::fields_type, security_id) == 8, "unexpected offset of top_of_book::fields_type::security_id");
static_assert(offsetof(top_of_book::fields_type, bid_px) == 16, "unexpected offset of top_of_book::fields_type::bid_px");
static_assert(offsetof(top_of_book::fields_type, offer_px) == 24, "unexpected offset of top_of_book::fields_type::offer_px");
static_assert(offsetof(top_of_book::fields_type, bid_size) == 32, "unexpected offset of top_of_book::fields_type::bid_size");
static_assert(offsetof(top_of_book::fields_type, offer_size) == 40, "unexpected offset of top_of_book::fields_type::offer_size");
static_assert(offsetof(top_of_book::fields_type, number_of_buy_orders) == 48, "unexpected offset of top_of_book::fields_type::number_of_buy_orders");
static_assert(offsetof(top_of_book::fields_type, number_of_sell_orders) == 50, "unexpected offset of top_of_book::fields_type::number_of_sell_orders");
static_assert(offsetof(top_of_book::fields_type, pad4) == 52, "unexpected offset of top_of_book::fields_type::pad4");
static_assert(sizeof(top_of_book::fields_type) == 56, "unexpected sizeof top_of_book::fields_type");
static_assert(sizeof(top_of_book) == sizeof(fbe_eobi::message_header_comp) + 56, "unexpected sizeof top_of_book");

#pragma pack(pop)
}
