#pragma once

#include <cstddef>
#include "../structs/MessageHeaderComp.hpp"
#include "../types/TransactTime.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastPx.hpp"
#include "../types/LastQty.hpp"
#include "../types/ImbalanceQty.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/PotentialSecurityTradingEvent.hpp"
#include "../types/Pad6.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

namespace fbe_eobi = ::eurex::t7::eobi::fbe::v15_0;

#pragma pack(push, 1)

// Auction Clearing Price
struct auction_clearing_price {

    struct fields_type {
        fbe_eobi::transact_time transact_time;
        fbe_eobi::security_id security_id;
        fbe_eobi::last_px last_px;
        fbe_eobi::last_qty last_qty;
        fbe_eobi::imbalance_qty imbalance_qty;
        fbe_eobi::security_trading_status security_trading_status;
        fbe_eobi::potential_security_trading_event potential_security_trading_event;
        fbe_eobi::pad6 pad6;
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
static_assert(offsetof(auction_clearing_price::fields_type, last_qty) == 24, "unexpected offset of auction_clearing_price::fields_type::last_qty");
static_assert(offsetof(auction_clearing_price::fields_type, imbalance_qty) == 32, "unexpected offset of auction_clearing_price::fields_type::imbalance_qty");
static_assert(offsetof(auction_clearing_price::fields_type, security_trading_status) == 40, "unexpected offset of auction_clearing_price::fields_type::security_trading_status");
static_assert(offsetof(auction_clearing_price::fields_type, potential_security_trading_event) == 41, "unexpected offset of auction_clearing_price::fields_type::potential_security_trading_event");
static_assert(offsetof(auction_clearing_price::fields_type, pad6) == 42, "unexpected offset of auction_clearing_price::fields_type::pad6");
static_assert(sizeof(auction_clearing_price::fields_type) == 48, "unexpected sizeof auction_clearing_price::fields_type");
static_assert(sizeof(auction_clearing_price) == sizeof(fbe_eobi::message_header_comp) + 48, "unexpected sizeof auction_clearing_price");

#pragma pack(pop)
}
