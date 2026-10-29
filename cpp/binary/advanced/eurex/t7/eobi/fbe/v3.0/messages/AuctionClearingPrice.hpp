#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastPx.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v3_0;

#pragma pack(push, 1)

// Auction Clearing Price
struct auction_clearing_price {

    struct fields_type {
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::last_px last_px;
    };

    fbe_eobi::message_header_comp header = {std::uint16_t(sizeof(fbe_eobi::message_header_comp) + sizeof(fields_type)), template_id::enum_type::auction_clearing_price, {}};

    fields_type fields;

    // parse method
    static auction_clearing_price* parse(std::byte* buffer) {
        return reinterpret_cast<auction_clearing_price*>(buffer);
    }

    // parse method const
    static const auction_clearing_price* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_clearing_price*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_clearing_price::fields_type, transact_time) == 0, "unexpected offset of auction_clearing_price::fields_type::transact_time");
static_assert(offsetof(auction_clearing_price::fields_type, security_id) == 8, "unexpected offset of auction_clearing_price::fields_type::security_id");
static_assert(offsetof(auction_clearing_price::fields_type, last_px) == 16, "unexpected offset of auction_clearing_price::fields_type::last_px");
static_assert(sizeof(auction_clearing_price::fields_type) == 24, "unexpected sizeof auction_clearing_price::fields_type");
static_assert(sizeof(auction_clearing_price) == sizeof(fbe_eobi::message_header_comp) + 24, "unexpected sizeof auction_clearing_price");

#pragma pack(pop)
}
