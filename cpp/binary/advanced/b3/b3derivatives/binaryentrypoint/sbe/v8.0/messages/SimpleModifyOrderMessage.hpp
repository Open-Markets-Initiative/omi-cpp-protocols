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
#include "../types/SimpleOrdtype.hpp"
#include "../types/TimeInForceSimple.hpp"
#include "../types/RoutingInstruction.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/OrderIdOptional.hpp"
#include "../types/Origclordid.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;


#pragma pack(push, 1)

// Simple Modify Order Message
struct simple_modify_order_message {

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
        sbe_binaryentrypoint::simple_ordtype simple_ordtype;
        sbe_binaryentrypoint::time_in_force_simple time_in_force_simple;
        sbe_binaryentrypoint::routing_instruction routing_instruction;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::price_optional price_optional;
        sbe_binaryentrypoint::order_id_optional order_id_optional;
        sbe_binaryentrypoint::origclordid origclordid;
        sbe_binaryentrypoint::investor_id investor_id;
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
    sbe_var_data memo() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static simple_modify_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<simple_modify_order_message*>(buffer);
    }

    // parse method const
    static const simple_modify_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const simple_modify_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(simple_modify_order_message::fields_type, inbound_business_header) == 0, "unexpected offset of simple_modify_order_message::fields_type::inbound_business_header");
static_assert(offsetof(simple_modify_order_message::fields_type, ordtagid) == 18, "unexpected offset of simple_modify_order_message::fields_type::ordtagid");
static_assert(offsetof(simple_modify_order_message::fields_type, mm_protection_reset) == 19, "unexpected offset of simple_modify_order_message::fields_type::mm_protection_reset");
static_assert(offsetof(simple_modify_order_message::fields_type, clordid) == 20, "unexpected offset of simple_modify_order_message::fields_type::clordid");
static_assert(offsetof(simple_modify_order_message::fields_type, account) == 28, "unexpected offset of simple_modify_order_message::fields_type::account");
static_assert(offsetof(simple_modify_order_message::fields_type, sender_location) == 32, "unexpected offset of simple_modify_order_message::fields_type::sender_location");
static_assert(offsetof(simple_modify_order_message::fields_type, entering_trader) == 42, "unexpected offset of simple_modify_order_message::fields_type::entering_trader");
static_assert(offsetof(simple_modify_order_message::fields_type, self_trade_prevention_instruction) == 47, "unexpected offset of simple_modify_order_message::fields_type::self_trade_prevention_instruction");
static_assert(offsetof(simple_modify_order_message::fields_type, security_id) == 48, "unexpected offset of simple_modify_order_message::fields_type::security_id");
static_assert(offsetof(simple_modify_order_message::fields_type, side) == 56, "unexpected offset of simple_modify_order_message::fields_type::side");
static_assert(offsetof(simple_modify_order_message::fields_type, simple_ordtype) == 57, "unexpected offset of simple_modify_order_message::fields_type::simple_ordtype");
static_assert(offsetof(simple_modify_order_message::fields_type, time_in_force_simple) == 58, "unexpected offset of simple_modify_order_message::fields_type::time_in_force_simple");
static_assert(offsetof(simple_modify_order_message::fields_type, routing_instruction) == 59, "unexpected offset of simple_modify_order_message::fields_type::routing_instruction");
static_assert(offsetof(simple_modify_order_message::fields_type, order_qty) == 60, "unexpected offset of simple_modify_order_message::fields_type::order_qty");
static_assert(offsetof(simple_modify_order_message::fields_type, price_optional) == 68, "unexpected offset of simple_modify_order_message::fields_type::price_optional");
static_assert(offsetof(simple_modify_order_message::fields_type, order_id_optional) == 76, "unexpected offset of simple_modify_order_message::fields_type::order_id_optional");
static_assert(offsetof(simple_modify_order_message::fields_type, origclordid) == 84, "unexpected offset of simple_modify_order_message::fields_type::origclordid");
static_assert(offsetof(simple_modify_order_message::fields_type, investor_id) == 92, "unexpected offset of simple_modify_order_message::fields_type::investor_id");
static_assert(sizeof(simple_modify_order_message::fields_type) == 100, "unexpected sizeof simple_modify_order_message::fields_type");

#pragma pack(pop)
}

#include "details/SimpleModifyOrderMessageWriter.hpp"
#include "details/SimpleModifyOrderMessageReader.hpp"
