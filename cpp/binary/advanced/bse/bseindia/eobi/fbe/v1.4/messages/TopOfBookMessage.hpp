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

// Top Of Book Message
struct top_of_book_message {

    struct fields_type {
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::bid_px bid_px;
        fbe_eobi::offer_px offer_px;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::top_of_book_message, {}};

    fields_type fields;

    // parse method
    static top_of_book_message* parse(std::byte* buffer) {
        return reinterpret_cast<top_of_book_message*>(buffer);
    }

    // parse method const
    static const top_of_book_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const top_of_book_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(top_of_book_message::fields_type, transact_time) == 0, "unexpected offset of top_of_book_message::fields_type::transact_time");
static_assert(offsetof(top_of_book_message::fields_type, security_id) == 8, "unexpected offset of top_of_book_message::fields_type::security_id");
static_assert(offsetof(top_of_book_message::fields_type, bid_px) == 16, "unexpected offset of top_of_book_message::fields_type::bid_px");
static_assert(offsetof(top_of_book_message::fields_type, offer_px) == 24, "unexpected offset of top_of_book_message::fields_type::offer_px");
static_assert(sizeof(top_of_book_message::fields_type) == 32, "unexpected sizeof top_of_book_message::fields_type");
static_assert(sizeof(top_of_book_message) == sizeof(fbe_eobi::message_header) + 32, "unexpected sizeof top_of_book_message");

#pragma pack(pop)
}
