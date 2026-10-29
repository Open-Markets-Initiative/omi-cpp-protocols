#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/BidPx.hpp"
#include "../types/OfferPx.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Top Of Book
struct top_of_book {

    struct fields_type {
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::bid_px bid_px;
        fbe_eobi::offer_px offer_px;
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
static_assert(sizeof(top_of_book::fields_type) == 32, "unexpected sizeof top_of_book::fields_type");
static_assert(sizeof(top_of_book) == sizeof(fbe_eobi::message_header_comp) + 32, "unexpected sizeof top_of_book");

#pragma pack(pop)
}
