#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Side.hpp"
#include "../types/CxlRejResponseTo.hpp"
#include "../types/Clordid.hpp"
#include "../types/SecondaryOrderIdOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrdRejReason.hpp"
#include "../types/TransactTime.hpp"
#include "../types/ExecId.hpp"
#include "../types/OrderIdOptional.hpp"
#include "../types/Origclordid.hpp"
#include "../types/Account.hpp"
#include "../types/Ordtype.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/ExpireDate.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/StopPx.hpp"
#include "../types/MinQty.hpp"
#include "../types/MaxFloor.hpp"
#include "../types/CrossidOptional.hpp"
#include "../types/CrossedIndicator.hpp"
#include "../types/ReceivedTime.hpp"
#include "../types/Offset146Padding3.hpp"
#include "../types/Ordtagid.hpp"
#include "../structs/InvestorId.hpp"
#include "../types/StrategyId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


#pragma pack(push, 1)

// Execution Report Reject Message
struct execution_report_reject_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::side side;
        sbe_binaryentrypoint::cxl_rej_response_to cxl_rej_response_to;
        sbe_binaryentrypoint::clordid clordid;
        sbe_binaryentrypoint::secondary_order_id_optional secondary_order_id_optional;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::ord_rej_reason ord_rej_reason;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::exec_id exec_id;
        sbe_binaryentrypoint::order_id_optional order_id_optional;
        sbe_binaryentrypoint::origclordid origclordid;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::ordtype ordtype;
        sbe_binaryentrypoint::time_in_force time_in_force;
        sbe_binaryentrypoint::expire_date expire_date;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::price_optional price_optional;
        sbe_binaryentrypoint::stop_px stop_px;
        sbe_binaryentrypoint::min_qty min_qty;
        sbe_binaryentrypoint::max_floor max_floor;
        sbe_binaryentrypoint::crossid_optional crossid_optional;
        sbe_binaryentrypoint::crossed_indicator crossed_indicator;
        sbe_binaryentrypoint::received_time received_time;
        sbe_binaryentrypoint::offset_146_padding_3 offset_146_padding_3;
        sbe_binaryentrypoint::ordtagid ordtagid;
        sbe_binaryentrypoint::investor_id investor_id;
        sbe_binaryentrypoint::strategy_id strategy_id;
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
    static execution_report_reject_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_report_reject_message*>(buffer);
    }

    // parse method const
    static const execution_report_reject_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_report_reject_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_report_reject_message::fields_type, outbound_business_header) == 0, "unexpected offset of execution_report_reject_message::fields_type::outbound_business_header");
static_assert(offsetof(execution_report_reject_message::fields_type, side) == 18, "unexpected offset of execution_report_reject_message::fields_type::side");
static_assert(offsetof(execution_report_reject_message::fields_type, cxl_rej_response_to) == 19, "unexpected offset of execution_report_reject_message::fields_type::cxl_rej_response_to");
static_assert(offsetof(execution_report_reject_message::fields_type, clordid) == 20, "unexpected offset of execution_report_reject_message::fields_type::clordid");
static_assert(offsetof(execution_report_reject_message::fields_type, secondary_order_id_optional) == 28, "unexpected offset of execution_report_reject_message::fields_type::secondary_order_id_optional");
static_assert(offsetof(execution_report_reject_message::fields_type, security_id) == 36, "unexpected offset of execution_report_reject_message::fields_type::security_id");
static_assert(offsetof(execution_report_reject_message::fields_type, ord_rej_reason) == 44, "unexpected offset of execution_report_reject_message::fields_type::ord_rej_reason");
static_assert(offsetof(execution_report_reject_message::fields_type, transact_time) == 48, "unexpected offset of execution_report_reject_message::fields_type::transact_time");
static_assert(offsetof(execution_report_reject_message::fields_type, exec_id) == 56, "unexpected offset of execution_report_reject_message::fields_type::exec_id");
static_assert(offsetof(execution_report_reject_message::fields_type, order_id_optional) == 64, "unexpected offset of execution_report_reject_message::fields_type::order_id_optional");
static_assert(offsetof(execution_report_reject_message::fields_type, origclordid) == 72, "unexpected offset of execution_report_reject_message::fields_type::origclordid");
static_assert(offsetof(execution_report_reject_message::fields_type, account) == 80, "unexpected offset of execution_report_reject_message::fields_type::account");
static_assert(offsetof(execution_report_reject_message::fields_type, ordtype) == 84, "unexpected offset of execution_report_reject_message::fields_type::ordtype");
static_assert(offsetof(execution_report_reject_message::fields_type, time_in_force) == 85, "unexpected offset of execution_report_reject_message::fields_type::time_in_force");
static_assert(offsetof(execution_report_reject_message::fields_type, expire_date) == 86, "unexpected offset of execution_report_reject_message::fields_type::expire_date");
static_assert(offsetof(execution_report_reject_message::fields_type, order_qty) == 88, "unexpected offset of execution_report_reject_message::fields_type::order_qty");
static_assert(offsetof(execution_report_reject_message::fields_type, price_optional) == 96, "unexpected offset of execution_report_reject_message::fields_type::price_optional");
static_assert(offsetof(execution_report_reject_message::fields_type, stop_px) == 104, "unexpected offset of execution_report_reject_message::fields_type::stop_px");
static_assert(offsetof(execution_report_reject_message::fields_type, min_qty) == 112, "unexpected offset of execution_report_reject_message::fields_type::min_qty");
static_assert(offsetof(execution_report_reject_message::fields_type, max_floor) == 120, "unexpected offset of execution_report_reject_message::fields_type::max_floor");
static_assert(offsetof(execution_report_reject_message::fields_type, crossid_optional) == 128, "unexpected offset of execution_report_reject_message::fields_type::crossid_optional");
static_assert(offsetof(execution_report_reject_message::fields_type, crossed_indicator) == 136, "unexpected offset of execution_report_reject_message::fields_type::crossed_indicator");
static_assert(offsetof(execution_report_reject_message::fields_type, received_time) == 138, "unexpected offset of execution_report_reject_message::fields_type::received_time");
static_assert(offsetof(execution_report_reject_message::fields_type, offset_146_padding_3) == 146, "unexpected offset of execution_report_reject_message::fields_type::offset_146_padding_3");
static_assert(offsetof(execution_report_reject_message::fields_type, ordtagid) == 149, "unexpected offset of execution_report_reject_message::fields_type::ordtagid");
static_assert(offsetof(execution_report_reject_message::fields_type, investor_id) == 150, "unexpected offset of execution_report_reject_message::fields_type::investor_id");
static_assert(offsetof(execution_report_reject_message::fields_type, strategy_id) == 158, "unexpected offset of execution_report_reject_message::fields_type::strategy_id");
static_assert(sizeof(execution_report_reject_message::fields_type) == 162, "unexpected sizeof execution_report_reject_message::fields_type");

#pragma pack(pop)
}

#include "details/ExecutionReportRejectMessageWriter.hpp"
#include "details/ExecutionReportRejectMessageReader.hpp"
