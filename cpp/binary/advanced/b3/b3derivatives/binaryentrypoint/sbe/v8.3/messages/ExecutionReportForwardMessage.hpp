#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Side.hpp"
#include "../types/OrdStatus.hpp"
#include "../types/ClordidOptional.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/Account.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/ExecId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/LeavesQty.hpp"
#include "../types/CumQty.hpp"
#include "../types/TradeId.hpp"
#include "../types/ContraBroker.hpp"
#include "../types/OrderId.hpp"
#include "../types/AggressorIndicator.hpp"
#include "../types/SettlTypeOptional.hpp"
#include "../types/TradeDate.hpp"
#include "../types/DaysToSettlementOptional.hpp"
#include "../types/Offset118Padding2.hpp"
#include "../types/SecondaryExecId.hpp"
#include "../types/ExecRefId.hpp"
#include "../types/FixedRatePercentage8Optional.hpp"
#include "../types/OrderQty.hpp"
#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;


#pragma pack(push, 1)

// Execution Report Forward Message
struct execution_report_forward_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::side side;
        sbe_binaryentrypoint::ord_status ord_status;
        sbe_binaryentrypoint::clordid_optional clordid_optional;
        sbe_binaryentrypoint::secondary_order_id secondary_order_id;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::last_qty last_qty;
        sbe_binaryentrypoint::last_px last_px;
        sbe_binaryentrypoint::exec_id exec_id;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::leaves_qty leaves_qty;
        sbe_binaryentrypoint::cum_qty cum_qty;
        sbe_binaryentrypoint::trade_id trade_id;
        sbe_binaryentrypoint::contra_broker contra_broker;
        sbe_binaryentrypoint::order_id order_id;
        sbe_binaryentrypoint::aggressor_indicator aggressor_indicator;
        sbe_binaryentrypoint::settl_type_optional settl_type_optional;
        sbe_binaryentrypoint::trade_date trade_date;
        sbe_binaryentrypoint::days_to_settlement_optional days_to_settlement_optional;
        sbe_binaryentrypoint::offset_118_padding_2 offset_118_padding_2;
        sbe_binaryentrypoint::secondary_exec_id secondary_exec_id;
        sbe_binaryentrypoint::exec_ref_id exec_ref_id;
        sbe_binaryentrypoint::fixed_rate_percentage_8_optional fixed_rate_percentage_8_optional;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::trading_session_id trading_session_id;
        sbe_binaryentrypoint::trading_session_sub_id trading_session_sub_id;
        sbe_binaryentrypoint::security_trading_status security_trading_status;
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
    static execution_report_forward_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_report_forward_message*>(buffer);
    }

    // parse method const
    static const execution_report_forward_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_report_forward_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_report_forward_message::fields_type, outbound_business_header) == 0, "unexpected offset of execution_report_forward_message::fields_type::outbound_business_header");
static_assert(offsetof(execution_report_forward_message::fields_type, side) == 18, "unexpected offset of execution_report_forward_message::fields_type::side");
static_assert(offsetof(execution_report_forward_message::fields_type, ord_status) == 19, "unexpected offset of execution_report_forward_message::fields_type::ord_status");
static_assert(offsetof(execution_report_forward_message::fields_type, clordid_optional) == 20, "unexpected offset of execution_report_forward_message::fields_type::clordid_optional");
static_assert(offsetof(execution_report_forward_message::fields_type, secondary_order_id) == 28, "unexpected offset of execution_report_forward_message::fields_type::secondary_order_id");
static_assert(offsetof(execution_report_forward_message::fields_type, security_id) == 36, "unexpected offset of execution_report_forward_message::fields_type::security_id");
static_assert(offsetof(execution_report_forward_message::fields_type, account) == 44, "unexpected offset of execution_report_forward_message::fields_type::account");
static_assert(offsetof(execution_report_forward_message::fields_type, last_qty) == 48, "unexpected offset of execution_report_forward_message::fields_type::last_qty");
static_assert(offsetof(execution_report_forward_message::fields_type, last_px) == 56, "unexpected offset of execution_report_forward_message::fields_type::last_px");
static_assert(offsetof(execution_report_forward_message::fields_type, exec_id) == 64, "unexpected offset of execution_report_forward_message::fields_type::exec_id");
static_assert(offsetof(execution_report_forward_message::fields_type, transact_time) == 72, "unexpected offset of execution_report_forward_message::fields_type::transact_time");
static_assert(offsetof(execution_report_forward_message::fields_type, leaves_qty) == 80, "unexpected offset of execution_report_forward_message::fields_type::leaves_qty");
static_assert(offsetof(execution_report_forward_message::fields_type, cum_qty) == 88, "unexpected offset of execution_report_forward_message::fields_type::cum_qty");
static_assert(offsetof(execution_report_forward_message::fields_type, trade_id) == 96, "unexpected offset of execution_report_forward_message::fields_type::trade_id");
static_assert(offsetof(execution_report_forward_message::fields_type, contra_broker) == 100, "unexpected offset of execution_report_forward_message::fields_type::contra_broker");
static_assert(offsetof(execution_report_forward_message::fields_type, order_id) == 104, "unexpected offset of execution_report_forward_message::fields_type::order_id");
static_assert(offsetof(execution_report_forward_message::fields_type, aggressor_indicator) == 112, "unexpected offset of execution_report_forward_message::fields_type::aggressor_indicator");
static_assert(offsetof(execution_report_forward_message::fields_type, settl_type_optional) == 113, "unexpected offset of execution_report_forward_message::fields_type::settl_type_optional");
static_assert(offsetof(execution_report_forward_message::fields_type, trade_date) == 114, "unexpected offset of execution_report_forward_message::fields_type::trade_date");
static_assert(offsetof(execution_report_forward_message::fields_type, days_to_settlement_optional) == 116, "unexpected offset of execution_report_forward_message::fields_type::days_to_settlement_optional");
static_assert(offsetof(execution_report_forward_message::fields_type, offset_118_padding_2) == 118, "unexpected offset of execution_report_forward_message::fields_type::offset_118_padding_2");
static_assert(offsetof(execution_report_forward_message::fields_type, secondary_exec_id) == 120, "unexpected offset of execution_report_forward_message::fields_type::secondary_exec_id");
static_assert(offsetof(execution_report_forward_message::fields_type, exec_ref_id) == 128, "unexpected offset of execution_report_forward_message::fields_type::exec_ref_id");
static_assert(offsetof(execution_report_forward_message::fields_type, fixed_rate_percentage_8_optional) == 136, "unexpected offset of execution_report_forward_message::fields_type::fixed_rate_percentage_8_optional");
static_assert(offsetof(execution_report_forward_message::fields_type, order_qty) == 144, "unexpected offset of execution_report_forward_message::fields_type::order_qty");
static_assert(offsetof(execution_report_forward_message::fields_type, trading_session_id) == 152, "unexpected offset of execution_report_forward_message::fields_type::trading_session_id");
static_assert(offsetof(execution_report_forward_message::fields_type, trading_session_sub_id) == 153, "unexpected offset of execution_report_forward_message::fields_type::trading_session_sub_id");
static_assert(offsetof(execution_report_forward_message::fields_type, security_trading_status) == 154, "unexpected offset of execution_report_forward_message::fields_type::security_trading_status");
static_assert(offsetof(execution_report_forward_message::fields_type, trading_sub_account) == 155, "unexpected offset of execution_report_forward_message::fields_type::trading_sub_account");
static_assert(sizeof(execution_report_forward_message::fields_type) == 159, "unexpected sizeof execution_report_forward_message::fields_type");

#pragma pack(pop)
}

#include "details/ExecutionReportForwardMessageWriter.hpp"
#include "details/ExecutionReportForwardMessageReader.hpp"
