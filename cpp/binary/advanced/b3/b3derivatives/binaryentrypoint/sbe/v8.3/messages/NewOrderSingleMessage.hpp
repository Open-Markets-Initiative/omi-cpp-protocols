#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../types/Ordtagid.hpp"
#include "../types/MmProtectionReset.hpp"
#include "../types/Clordid.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/SelfTradePreventionInstruction.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Side.hpp"
#include "../types/Ordtype.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/RoutingInstruction.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/StopPx.hpp"
#include "../types/MinQty.hpp"
#include "../types/MaxFloor.hpp"
#include "../types/ExecutingTraderOptional.hpp"
#include "../types/ExpireDate.hpp"
#include "../structs/CustodianInfo.hpp"
#include "../structs/InvestorId.hpp"
#include "../types/StrategyId.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;


#pragma pack(push, 1)

// New Order Single Message
struct new_order_single_message {

    struct fields_type {
        sbe_binaryentrypoint::inbound_business_header inbound_business_header;
        sbe_binaryentrypoint::ordtagid ordtagid;
        sbe_binaryentrypoint::mm_protection_reset mm_protection_reset;
        sbe_binaryentrypoint::clordid clordid;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::self_trade_prevention_instruction self_trade_prevention_instruction;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::side side;
        sbe_binaryentrypoint::ordtype ordtype;
        sbe_binaryentrypoint::time_in_force time_in_force;
        sbe_binaryentrypoint::routing_instruction routing_instruction;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::price_optional price_optional;
        sbe_binaryentrypoint::stop_px stop_px;
        sbe_binaryentrypoint::min_qty min_qty;
        sbe_binaryentrypoint::max_floor max_floor;
        sbe_binaryentrypoint::executing_trader_optional executing_trader_optional;
        sbe_binaryentrypoint::expire_date expire_date;
        sbe_binaryentrypoint::custodian_info custodian_info;
        sbe_binaryentrypoint::investor_id investor_id;
        sbe_binaryentrypoint::strategy_id strategy_id;
        sbe_binaryentrypoint::trading_sub_account trading_sub_account;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_binaryentrypoint::simple_open_framing_header) - sizeof(fields_type) - sizeof(sbe_binaryentrypoint::message_header);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return sz == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_binaryentrypoint::simple_open_framing_header) - sizeof(fields_type) - sizeof(sbe_binaryentrypoint::message_header));
    }

    // sequential access to variable-length regions
    sbe_var_data desk_id() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data memo(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static new_order_single_message* parse(std::byte* buffer) {
        return reinterpret_cast<new_order_single_message*>(buffer);
    }

    // parse method const
    static const new_order_single_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const new_order_single_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(new_order_single_message::fields_type, inbound_business_header) == 0, "unexpected offset of new_order_single_message::fields_type::inbound_business_header");
static_assert(offsetof(new_order_single_message::fields_type, ordtagid) == 18, "unexpected offset of new_order_single_message::fields_type::ordtagid");
static_assert(offsetof(new_order_single_message::fields_type, mm_protection_reset) == 19, "unexpected offset of new_order_single_message::fields_type::mm_protection_reset");
static_assert(offsetof(new_order_single_message::fields_type, clordid) == 20, "unexpected offset of new_order_single_message::fields_type::clordid");
static_assert(offsetof(new_order_single_message::fields_type, account) == 28, "unexpected offset of new_order_single_message::fields_type::account");
static_assert(offsetof(new_order_single_message::fields_type, sender_location) == 32, "unexpected offset of new_order_single_message::fields_type::sender_location");
static_assert(offsetof(new_order_single_message::fields_type, entering_trader) == 42, "unexpected offset of new_order_single_message::fields_type::entering_trader");
static_assert(offsetof(new_order_single_message::fields_type, self_trade_prevention_instruction) == 47, "unexpected offset of new_order_single_message::fields_type::self_trade_prevention_instruction");
static_assert(offsetof(new_order_single_message::fields_type, security_id) == 48, "unexpected offset of new_order_single_message::fields_type::security_id");
static_assert(offsetof(new_order_single_message::fields_type, side) == 56, "unexpected offset of new_order_single_message::fields_type::side");
static_assert(offsetof(new_order_single_message::fields_type, ordtype) == 57, "unexpected offset of new_order_single_message::fields_type::ordtype");
static_assert(offsetof(new_order_single_message::fields_type, time_in_force) == 58, "unexpected offset of new_order_single_message::fields_type::time_in_force");
static_assert(offsetof(new_order_single_message::fields_type, routing_instruction) == 59, "unexpected offset of new_order_single_message::fields_type::routing_instruction");
static_assert(offsetof(new_order_single_message::fields_type, order_qty) == 60, "unexpected offset of new_order_single_message::fields_type::order_qty");
static_assert(offsetof(new_order_single_message::fields_type, price_optional) == 68, "unexpected offset of new_order_single_message::fields_type::price_optional");
static_assert(offsetof(new_order_single_message::fields_type, stop_px) == 76, "unexpected offset of new_order_single_message::fields_type::stop_px");
static_assert(offsetof(new_order_single_message::fields_type, min_qty) == 84, "unexpected offset of new_order_single_message::fields_type::min_qty");
static_assert(offsetof(new_order_single_message::fields_type, max_floor) == 92, "unexpected offset of new_order_single_message::fields_type::max_floor");
static_assert(offsetof(new_order_single_message::fields_type, executing_trader_optional) == 100, "unexpected offset of new_order_single_message::fields_type::executing_trader_optional");
static_assert(offsetof(new_order_single_message::fields_type, expire_date) == 105, "unexpected offset of new_order_single_message::fields_type::expire_date");
static_assert(offsetof(new_order_single_message::fields_type, custodian_info) == 107, "unexpected offset of new_order_single_message::fields_type::custodian_info");
static_assert(offsetof(new_order_single_message::fields_type, investor_id) == 119, "unexpected offset of new_order_single_message::fields_type::investor_id");
static_assert(offsetof(new_order_single_message::fields_type, strategy_id) == 127, "unexpected offset of new_order_single_message::fields_type::strategy_id");
static_assert(offsetof(new_order_single_message::fields_type, trading_sub_account) == 131, "unexpected offset of new_order_single_message::fields_type::trading_sub_account");
static_assert(sizeof(new_order_single_message::fields_type) == 135, "unexpected sizeof new_order_single_message::fields_type");

#pragma pack(pop)
}

#include "details/NewOrderSingleMessageWriter.hpp"
#include "details/NewOrderSingleMessageReader.hpp"
