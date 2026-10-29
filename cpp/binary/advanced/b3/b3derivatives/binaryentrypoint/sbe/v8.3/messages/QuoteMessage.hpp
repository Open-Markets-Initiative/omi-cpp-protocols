#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteReqId.hpp"
#include "../types/QuoteId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/Price8Optional.hpp"
#include "../types/OrderQty.hpp"
#include "../types/Side.hpp"
#include "../types/SettlType.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTrader.hpp"
#include "../types/FixedRatePercentage8.hpp"
#include "../types/ExecuteUnderlyingTrade.hpp"
#include "../types/DaysToSettlement.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;


#pragma pack(push, 1)

// Quote Message
struct quote_message {

    struct fields_type {
        sbe_binaryentrypoint::bidirectional_business_header bidirectional_business_header;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::quote_req_id quote_req_id;
        sbe_binaryentrypoint::quote_id quote_id;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::price_8_optional price_8_optional;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::side side;
        sbe_binaryentrypoint::settl_type settl_type;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::executing_trader executing_trader;
        sbe_binaryentrypoint::fixed_rate_percentage_8 fixed_rate_percentage_8;
        sbe_binaryentrypoint::execute_underlying_trade execute_underlying_trade;
        sbe_binaryentrypoint::days_to_settlement days_to_settlement;
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
    static quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_message*>(buffer);
    }

    // parse method const
    static const quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_message::fields_type, bidirectional_business_header) == 0, "unexpected offset of quote_message::fields_type::bidirectional_business_header");
static_assert(offsetof(quote_message::fields_type, security_id) == 19, "unexpected offset of quote_message::fields_type::security_id");
static_assert(offsetof(quote_message::fields_type, quote_req_id) == 27, "unexpected offset of quote_message::fields_type::quote_req_id");
static_assert(offsetof(quote_message::fields_type, quote_id) == 35, "unexpected offset of quote_message::fields_type::quote_id");
static_assert(offsetof(quote_message::fields_type, transact_time) == 43, "unexpected offset of quote_message::fields_type::transact_time");
static_assert(offsetof(quote_message::fields_type, price_8_optional) == 51, "unexpected offset of quote_message::fields_type::price_8_optional");
static_assert(offsetof(quote_message::fields_type, order_qty) == 59, "unexpected offset of quote_message::fields_type::order_qty");
static_assert(offsetof(quote_message::fields_type, side) == 67, "unexpected offset of quote_message::fields_type::side");
static_assert(offsetof(quote_message::fields_type, settl_type) == 68, "unexpected offset of quote_message::fields_type::settl_type");
static_assert(offsetof(quote_message::fields_type, account) == 69, "unexpected offset of quote_message::fields_type::account");
static_assert(offsetof(quote_message::fields_type, sender_location) == 73, "unexpected offset of quote_message::fields_type::sender_location");
static_assert(offsetof(quote_message::fields_type, entering_trader) == 83, "unexpected offset of quote_message::fields_type::entering_trader");
static_assert(offsetof(quote_message::fields_type, executing_trader) == 88, "unexpected offset of quote_message::fields_type::executing_trader");
static_assert(offsetof(quote_message::fields_type, fixed_rate_percentage_8) == 93, "unexpected offset of quote_message::fields_type::fixed_rate_percentage_8");
static_assert(offsetof(quote_message::fields_type, execute_underlying_trade) == 101, "unexpected offset of quote_message::fields_type::execute_underlying_trade");
static_assert(offsetof(quote_message::fields_type, days_to_settlement) == 102, "unexpected offset of quote_message::fields_type::days_to_settlement");
static_assert(offsetof(quote_message::fields_type, trading_sub_account) == 104, "unexpected offset of quote_message::fields_type::trading_sub_account");
static_assert(sizeof(quote_message::fields_type) == 108, "unexpected sizeof quote_message::fields_type");

#pragma pack(pop)
}

#include "details/QuoteMessageWriter.hpp"
#include "details/QuoteMessageReader.hpp"
