#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/QuoteRequestRejectReason.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteIdOptional.hpp"
#include "../types/TradeIdOptional.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/TransactTime.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/SettlTypeOptional.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/OrderQtyOptional.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/ExecutingTrader.hpp"
#include "../types/FixedRateOptional.hpp"
#include "../types/DaysToSettlementOptional.hpp"
#include "../types/Side.hpp"
#include "../types/Account.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)
struct quote_request_reject_message_sides_groups_entry {
    sbe_binaryentrypoint::side side;
    sbe_binaryentrypoint::account account;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Quote Request Reject Message
struct quote_request_reject_message {

    struct fields_type {
        sbe_binaryentrypoint::bidirectional_business_header bidirectional_business_header;
        sbe_binaryentrypoint::quote_request_reject_reason quote_request_reject_reason;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::quote_id_optional quote_id_optional;
        sbe_binaryentrypoint::trade_id_optional trade_id_optional;
        sbe_binaryentrypoint::contra_broker contra_broker;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::settl_type_optional settl_type_optional;
        sbe_binaryentrypoint::price_optional price_optional;
        sbe_binaryentrypoint::order_qty_optional order_qty_optional;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::executing_trader executing_trader;
        sbe_binaryentrypoint::fixed_rate_optional fixed_rate_optional;
        sbe_binaryentrypoint::days_to_settlement_optional days_to_settlement_optional;
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
    sbe_group_iterator<quote_request_reject_message_sides_groups_entry, group_size_encoding> sides_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data quote_req_id(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data desk_id(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data memo(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data text(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static quote_request_reject_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_request_reject_message*>(buffer);
    }

    // parse method const
    static const quote_request_reject_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_request_reject_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_request_reject_message::fields_type, bidirectional_business_header) == 0, "unexpected offset of quote_request_reject_message::fields_type::bidirectional_business_header");
static_assert(offsetof(quote_request_reject_message::fields_type, quote_request_reject_reason) == 19, "unexpected offset of quote_request_reject_message::fields_type::quote_request_reject_reason");
static_assert(offsetof(quote_request_reject_message::fields_type, security_id) == 23, "unexpected offset of quote_request_reject_message::fields_type::security_id");
static_assert(offsetof(quote_request_reject_message::fields_type, quote_id_optional) == 31, "unexpected offset of quote_request_reject_message::fields_type::quote_id_optional");
static_assert(offsetof(quote_request_reject_message::fields_type, trade_id_optional) == 39, "unexpected offset of quote_request_reject_message::fields_type::trade_id_optional");
static_assert(offsetof(quote_request_reject_message::fields_type, contra_broker) == 43, "unexpected offset of quote_request_reject_message::fields_type::contra_broker");
static_assert(offsetof(quote_request_reject_message::fields_type, transact_time) == 47, "unexpected offset of quote_request_reject_message::fields_type::transact_time");
static_assert(offsetof(quote_request_reject_message::fields_type, entering_trader) == 55, "unexpected offset of quote_request_reject_message::fields_type::entering_trader");
static_assert(offsetof(quote_request_reject_message::fields_type, settl_type_optional) == 60, "unexpected offset of quote_request_reject_message::fields_type::settl_type_optional");
static_assert(offsetof(quote_request_reject_message::fields_type, price_optional) == 61, "unexpected offset of quote_request_reject_message::fields_type::price_optional");
static_assert(offsetof(quote_request_reject_message::fields_type, order_qty_optional) == 69, "unexpected offset of quote_request_reject_message::fields_type::order_qty_optional");
static_assert(offsetof(quote_request_reject_message::fields_type, sender_location) == 77, "unexpected offset of quote_request_reject_message::fields_type::sender_location");
static_assert(offsetof(quote_request_reject_message::fields_type, executing_trader) == 87, "unexpected offset of quote_request_reject_message::fields_type::executing_trader");
static_assert(offsetof(quote_request_reject_message::fields_type, fixed_rate_optional) == 92, "unexpected offset of quote_request_reject_message::fields_type::fixed_rate_optional");
static_assert(offsetof(quote_request_reject_message::fields_type, days_to_settlement_optional) == 100, "unexpected offset of quote_request_reject_message::fields_type::days_to_settlement_optional");
static_assert(sizeof(quote_request_reject_message::fields_type) == 102, "unexpected sizeof quote_request_reject_message::fields_type");

#pragma pack(pop)
}

#include "details/QuoteRequestRejectMessageWriter.hpp"
#include "details/QuoteRequestRejectMessageReader.hpp"
