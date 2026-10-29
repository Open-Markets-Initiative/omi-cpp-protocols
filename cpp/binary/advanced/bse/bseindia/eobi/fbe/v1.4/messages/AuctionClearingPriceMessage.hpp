#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastPx.hpp"
#include "../types/LastQty.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

namespace fbe_eobi = ::bse::bseindia::eobi::fbe::v1_4;

#pragma pack(push, 1)

// Auction Clearing Price Message
struct auction_clearing_price_message {

    struct fields_type {
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::last_px last_px;
        fbe_eobi::last_qty last_qty;
    };

    fbe_eobi::message_header header = {std::uint16_t(sizeof(fbe_eobi::message_header) + sizeof(fields_type)), template_id::enum_type::auction_clearing_price_message, {}};

    fields_type fields;

    // parse method
    static auction_clearing_price_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_clearing_price_message*>(buffer);
    }

    // parse method const
    static const auction_clearing_price_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_clearing_price_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_clearing_price_message::fields_type, transact_time) == 0, "unexpected offset of auction_clearing_price_message::fields_type::transact_time");
static_assert(offsetof(auction_clearing_price_message::fields_type, security_id) == 8, "unexpected offset of auction_clearing_price_message::fields_type::security_id");
static_assert(offsetof(auction_clearing_price_message::fields_type, last_px) == 16, "unexpected offset of auction_clearing_price_message::fields_type::last_px");
static_assert(offsetof(auction_clearing_price_message::fields_type, last_qty) == 24, "unexpected offset of auction_clearing_price_message::fields_type::last_qty");
static_assert(sizeof(auction_clearing_price_message::fields_type) == 32, "unexpected sizeof auction_clearing_price_message::fields_type");
static_assert(sizeof(auction_clearing_price_message) == sizeof(fbe_eobi::message_header) + 32, "unexpected sizeof auction_clearing_price_message");

#pragma pack(pop)
}
