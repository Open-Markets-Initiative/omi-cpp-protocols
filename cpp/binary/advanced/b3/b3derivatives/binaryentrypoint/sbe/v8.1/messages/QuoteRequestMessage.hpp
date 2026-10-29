#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteReqId.hpp"
#include "../types/QuoteIdOptional.hpp"
#include "../types/TradeIdOptional.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/TransactTime.hpp"
#include "../types/Price8.hpp"
#include "../types/SettlType.hpp"
#include "../types/ExecuteUnderlyingTrade.hpp"
#include "../types/OrderQty.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTrader.hpp"
#include "../types/FixedRatePercentage8.hpp"
#include "../types/DaysToSettlement.hpp"
#include "../types/Side.hpp"
#include "../types/Account.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)
struct quote_request_message_sides_groups_entry {
    sbe_binaryentrypoint::side side;
    sbe_binaryentrypoint::account account;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Quote Request Message
struct quote_request_message {

    struct fields_type {
        sbe_binaryentrypoint::bidirectional_business_header bidirectional_business_header;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::quote_req_id quote_req_id;
        sbe_binaryentrypoint::quote_id_optional quote_id_optional;
        sbe_binaryentrypoint::trade_id_optional trade_id_optional;
        sbe_binaryentrypoint::contra_broker contra_broker;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::price_8 price_8;
        sbe_binaryentrypoint::settl_type settl_type;
        sbe_binaryentrypoint::execute_underlying_trade execute_underlying_trade;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::executing_trader executing_trader;
        sbe_binaryentrypoint::fixed_rate_percentage_8 fixed_rate_percentage_8;
        sbe_binaryentrypoint::days_to_settlement days_to_settlement;
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
    sbe_group_iterator<quote_request_message_sides_groups_entry, group_size_encoding> sides_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data desk_id(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data memo(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static quote_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_request_message*>(buffer);
    }

    // parse method const
    static const quote_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_request_message::fields_type, bidirectional_business_header) == 0, "unexpected offset of quote_request_message::fields_type::bidirectional_business_header");
static_assert(offsetof(quote_request_message::fields_type, security_id) == 19, "unexpected offset of quote_request_message::fields_type::security_id");
static_assert(offsetof(quote_request_message::fields_type, quote_req_id) == 27, "unexpected offset of quote_request_message::fields_type::quote_req_id");
static_assert(offsetof(quote_request_message::fields_type, quote_id_optional) == 35, "unexpected offset of quote_request_message::fields_type::quote_id_optional");
static_assert(offsetof(quote_request_message::fields_type, trade_id_optional) == 43, "unexpected offset of quote_request_message::fields_type::trade_id_optional");
static_assert(offsetof(quote_request_message::fields_type, contra_broker) == 47, "unexpected offset of quote_request_message::fields_type::contra_broker");
static_assert(offsetof(quote_request_message::fields_type, transact_time) == 51, "unexpected offset of quote_request_message::fields_type::transact_time");
static_assert(offsetof(quote_request_message::fields_type, price_8) == 59, "unexpected offset of quote_request_message::fields_type::price_8");
static_assert(offsetof(quote_request_message::fields_type, settl_type) == 67, "unexpected offset of quote_request_message::fields_type::settl_type");
static_assert(offsetof(quote_request_message::fields_type, execute_underlying_trade) == 68, "unexpected offset of quote_request_message::fields_type::execute_underlying_trade");
static_assert(offsetof(quote_request_message::fields_type, order_qty) == 69, "unexpected offset of quote_request_message::fields_type::order_qty");
static_assert(offsetof(quote_request_message::fields_type, sender_location) == 77, "unexpected offset of quote_request_message::fields_type::sender_location");
static_assert(offsetof(quote_request_message::fields_type, entering_trader) == 87, "unexpected offset of quote_request_message::fields_type::entering_trader");
static_assert(offsetof(quote_request_message::fields_type, executing_trader) == 92, "unexpected offset of quote_request_message::fields_type::executing_trader");
static_assert(offsetof(quote_request_message::fields_type, fixed_rate_percentage_8) == 97, "unexpected offset of quote_request_message::fields_type::fixed_rate_percentage_8");
static_assert(offsetof(quote_request_message::fields_type, days_to_settlement) == 105, "unexpected offset of quote_request_message::fields_type::days_to_settlement");
static_assert(sizeof(quote_request_message::fields_type) == 107, "unexpected sizeof quote_request_message::fields_type");

#pragma pack(pop)
}

#include "details/QuoteRequestMessageWriter.hpp"
#include "details/QuoteRequestMessageReader.hpp"
