#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../types/Offset18Padding2.hpp"
#include "../types/Crossid.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTraderOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderQty.hpp"
#include "../types/Price.hpp"
#include "../types/CrossedIndicator.hpp"
#include "../types/Side.hpp"
#include "../types/Offset1Padding1.hpp"
#include "../types/Account.hpp"
#include "../types/EnteringFirmOptional.hpp"
#include "../types/Clordid.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)
struct new_order_cross_message_cross_sides_groups_entry {
    sbe_binaryentrypoint::side side;
    sbe_binaryentrypoint::offset_1_padding_1 offset_1_padding_1;
    sbe_binaryentrypoint::account account;
    sbe_binaryentrypoint::entering_firm_optional entering_firm_optional;
    sbe_binaryentrypoint::clordid clordid;
};
#pragma pack(pop)


#pragma pack(push, 1)

// New Order Cross Message
struct new_order_cross_message {

    struct fields_type {
        sbe_binaryentrypoint::inbound_business_header inbound_business_header;
        sbe_binaryentrypoint::offset_18_padding_2 offset_18_padding_2;
        sbe_binaryentrypoint::crossid crossid;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::executing_trader_optional executing_trader_optional;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::price price;
        sbe_binaryentrypoint::crossed_indicator crossed_indicator;
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
    sbe_group_iterator<new_order_cross_message_cross_sides_groups_entry, group_size_encoding> cross_sides_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data desk_id(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data memo(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static new_order_cross_message* parse(std::byte* buffer) {
        return reinterpret_cast<new_order_cross_message*>(buffer);
    }

    // parse method const
    static const new_order_cross_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const new_order_cross_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(new_order_cross_message::fields_type, inbound_business_header) == 0, "unexpected offset of new_order_cross_message::fields_type::inbound_business_header");
static_assert(offsetof(new_order_cross_message::fields_type, offset_18_padding_2) == 18, "unexpected offset of new_order_cross_message::fields_type::offset_18_padding_2");
static_assert(offsetof(new_order_cross_message::fields_type, crossid) == 20, "unexpected offset of new_order_cross_message::fields_type::crossid");
static_assert(offsetof(new_order_cross_message::fields_type, sender_location) == 28, "unexpected offset of new_order_cross_message::fields_type::sender_location");
static_assert(offsetof(new_order_cross_message::fields_type, entering_trader) == 38, "unexpected offset of new_order_cross_message::fields_type::entering_trader");
static_assert(offsetof(new_order_cross_message::fields_type, executing_trader_optional) == 43, "unexpected offset of new_order_cross_message::fields_type::executing_trader_optional");
static_assert(offsetof(new_order_cross_message::fields_type, security_id) == 48, "unexpected offset of new_order_cross_message::fields_type::security_id");
static_assert(offsetof(new_order_cross_message::fields_type, order_qty) == 56, "unexpected offset of new_order_cross_message::fields_type::order_qty");
static_assert(offsetof(new_order_cross_message::fields_type, price) == 64, "unexpected offset of new_order_cross_message::fields_type::price");
static_assert(offsetof(new_order_cross_message::fields_type, crossed_indicator) == 72, "unexpected offset of new_order_cross_message::fields_type::crossed_indicator");
static_assert(sizeof(new_order_cross_message::fields_type) == 74, "unexpected sizeof new_order_cross_message::fields_type");

#pragma pack(pop)
}

#include "details/NewOrderCrossMessageWriter.hpp"
#include "details/NewOrderCrossMessageReader.hpp"
