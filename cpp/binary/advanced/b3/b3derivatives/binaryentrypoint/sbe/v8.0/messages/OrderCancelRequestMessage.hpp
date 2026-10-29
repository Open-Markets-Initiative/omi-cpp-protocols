#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../types/Offset18Padding2.hpp"
#include "../types/Clordid.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderIdOptional.hpp"
#include "../types/Origclordid.hpp"
#include "../types/Side.hpp"
#include "../types/SingleCancelRestatementReason.hpp"
#include "../types/Offset54Padding2.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTraderOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;


#pragma pack(push, 1)

// Order Cancel Request Message
struct order_cancel_request_message {

    struct fields_type {
        sbe_binaryentrypoint::inbound_business_header inbound_business_header;
        sbe_binaryentrypoint::offset_18_padding_2 offset_18_padding_2;
        sbe_binaryentrypoint::clordid clordid;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::order_id_optional order_id_optional;
        sbe_binaryentrypoint::origclordid origclordid;
        sbe_binaryentrypoint::side side;
        sbe_binaryentrypoint::single_cancel_restatement_reason single_cancel_restatement_reason;
        sbe_binaryentrypoint::offset_54_padding_2 offset_54_padding_2;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::executing_trader_optional executing_trader_optional;
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
    static order_cancel_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_cancel_request_message*>(buffer);
    }

    // parse method const
    static const order_cancel_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_cancel_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_cancel_request_message::fields_type, inbound_business_header) == 0, "unexpected offset of order_cancel_request_message::fields_type::inbound_business_header");
static_assert(offsetof(order_cancel_request_message::fields_type, offset_18_padding_2) == 18, "unexpected offset of order_cancel_request_message::fields_type::offset_18_padding_2");
static_assert(offsetof(order_cancel_request_message::fields_type, clordid) == 20, "unexpected offset of order_cancel_request_message::fields_type::clordid");
static_assert(offsetof(order_cancel_request_message::fields_type, security_id) == 28, "unexpected offset of order_cancel_request_message::fields_type::security_id");
static_assert(offsetof(order_cancel_request_message::fields_type, order_id_optional) == 36, "unexpected offset of order_cancel_request_message::fields_type::order_id_optional");
static_assert(offsetof(order_cancel_request_message::fields_type, origclordid) == 44, "unexpected offset of order_cancel_request_message::fields_type::origclordid");
static_assert(offsetof(order_cancel_request_message::fields_type, side) == 52, "unexpected offset of order_cancel_request_message::fields_type::side");
static_assert(offsetof(order_cancel_request_message::fields_type, single_cancel_restatement_reason) == 53, "unexpected offset of order_cancel_request_message::fields_type::single_cancel_restatement_reason");
static_assert(offsetof(order_cancel_request_message::fields_type, offset_54_padding_2) == 54, "unexpected offset of order_cancel_request_message::fields_type::offset_54_padding_2");
static_assert(offsetof(order_cancel_request_message::fields_type, sender_location) == 56, "unexpected offset of order_cancel_request_message::fields_type::sender_location");
static_assert(offsetof(order_cancel_request_message::fields_type, entering_trader) == 66, "unexpected offset of order_cancel_request_message::fields_type::entering_trader");
static_assert(offsetof(order_cancel_request_message::fields_type, executing_trader_optional) == 71, "unexpected offset of order_cancel_request_message::fields_type::executing_trader_optional");
static_assert(sizeof(order_cancel_request_message::fields_type) == 76, "unexpected sizeof order_cancel_request_message::fields_type");

#pragma pack(pop)
}

#include "details/OrderCancelRequestMessageWriter.hpp"
#include "details/OrderCancelRequestMessageReader.hpp"
