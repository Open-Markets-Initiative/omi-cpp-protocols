#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/BidirectionalBusinessHeader.hpp"
#include "../types/QuoteRejectReason.hpp"
#include "../types/SecurityId.hpp"
#include "../types/QuoteReqId.hpp"
#include "../types/QuoteId.hpp"
#include "../types/TradeIdOptional.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/TransactTime.hpp"
#include "../types/QuoteStatus.hpp"
#include "../types/QuoteStatusResponseTo.hpp"
#include "../types/Account.hpp"
#include "../types/SideOptional.hpp"
#include "../types/SettlTypeOptional.hpp"
#include "../types/Price8Optional.hpp"
#include "../types/OrderQty.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/ExecutingTrader.hpp"
#include "../types/FixedRatePercentage8Optional.hpp"
#include "../types/ExecuteUnderlyingTrade.hpp"
#include "../types/DaysToSettlementOptional.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


#pragma pack(push, 1)

// Quote Status Report Message
struct quote_status_report_message {

    struct fields_type {
        sbe_binaryentrypoint::bidirectional_business_header bidirectional_business_header;
        sbe_binaryentrypoint::quote_reject_reason quote_reject_reason;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::quote_req_id quote_req_id;
        sbe_binaryentrypoint::quote_id quote_id;
        sbe_binaryentrypoint::trade_id_optional trade_id_optional;
        sbe_binaryentrypoint::contra_broker contra_broker;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::quote_status quote_status;
        sbe_binaryentrypoint::quote_status_response_to quote_status_response_to;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::side_optional side_optional;
        sbe_binaryentrypoint::settl_type_optional settl_type_optional;
        sbe_binaryentrypoint::price_8_optional price_8_optional;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::executing_trader executing_trader;
        sbe_binaryentrypoint::fixed_rate_percentage_8_optional fixed_rate_percentage_8_optional;
        sbe_binaryentrypoint::execute_underlying_trade execute_underlying_trade;
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
    sbe_var_data desk_id() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data memo(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data text(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static quote_status_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_status_report_message*>(buffer);
    }

    // parse method const
    static const quote_status_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_status_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_status_report_message::fields_type, bidirectional_business_header) == 0, "unexpected offset of quote_status_report_message::fields_type::bidirectional_business_header");
static_assert(offsetof(quote_status_report_message::fields_type, quote_reject_reason) == 19, "unexpected offset of quote_status_report_message::fields_type::quote_reject_reason");
static_assert(offsetof(quote_status_report_message::fields_type, security_id) == 23, "unexpected offset of quote_status_report_message::fields_type::security_id");
static_assert(offsetof(quote_status_report_message::fields_type, quote_req_id) == 31, "unexpected offset of quote_status_report_message::fields_type::quote_req_id");
static_assert(offsetof(quote_status_report_message::fields_type, quote_id) == 39, "unexpected offset of quote_status_report_message::fields_type::quote_id");
static_assert(offsetof(quote_status_report_message::fields_type, trade_id_optional) == 47, "unexpected offset of quote_status_report_message::fields_type::trade_id_optional");
static_assert(offsetof(quote_status_report_message::fields_type, contra_broker) == 51, "unexpected offset of quote_status_report_message::fields_type::contra_broker");
static_assert(offsetof(quote_status_report_message::fields_type, transact_time) == 55, "unexpected offset of quote_status_report_message::fields_type::transact_time");
static_assert(offsetof(quote_status_report_message::fields_type, quote_status) == 63, "unexpected offset of quote_status_report_message::fields_type::quote_status");
static_assert(offsetof(quote_status_report_message::fields_type, quote_status_response_to) == 64, "unexpected offset of quote_status_report_message::fields_type::quote_status_response_to");
static_assert(offsetof(quote_status_report_message::fields_type, account) == 65, "unexpected offset of quote_status_report_message::fields_type::account");
static_assert(offsetof(quote_status_report_message::fields_type, side_optional) == 69, "unexpected offset of quote_status_report_message::fields_type::side_optional");
static_assert(offsetof(quote_status_report_message::fields_type, settl_type_optional) == 70, "unexpected offset of quote_status_report_message::fields_type::settl_type_optional");
static_assert(offsetof(quote_status_report_message::fields_type, price_8_optional) == 71, "unexpected offset of quote_status_report_message::fields_type::price_8_optional");
static_assert(offsetof(quote_status_report_message::fields_type, order_qty) == 79, "unexpected offset of quote_status_report_message::fields_type::order_qty");
static_assert(offsetof(quote_status_report_message::fields_type, sender_location) == 87, "unexpected offset of quote_status_report_message::fields_type::sender_location");
static_assert(offsetof(quote_status_report_message::fields_type, entering_trader) == 97, "unexpected offset of quote_status_report_message::fields_type::entering_trader");
static_assert(offsetof(quote_status_report_message::fields_type, executing_trader) == 102, "unexpected offset of quote_status_report_message::fields_type::executing_trader");
static_assert(offsetof(quote_status_report_message::fields_type, fixed_rate_percentage_8_optional) == 107, "unexpected offset of quote_status_report_message::fields_type::fixed_rate_percentage_8_optional");
static_assert(offsetof(quote_status_report_message::fields_type, execute_underlying_trade) == 115, "unexpected offset of quote_status_report_message::fields_type::execute_underlying_trade");
static_assert(offsetof(quote_status_report_message::fields_type, days_to_settlement_optional) == 116, "unexpected offset of quote_status_report_message::fields_type::days_to_settlement_optional");
static_assert(sizeof(quote_status_report_message::fields_type) == 118, "unexpected sizeof quote_status_report_message::fields_type");

#pragma pack(pop)
}

#include "details/QuoteStatusReportMessageWriter.hpp"
#include "details/QuoteStatusReportMessageReader.hpp"
