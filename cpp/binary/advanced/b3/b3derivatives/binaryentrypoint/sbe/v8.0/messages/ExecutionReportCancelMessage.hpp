#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Side.hpp"
#include "../types/OrdStatus.hpp"
#include "../types/Clordid.hpp"
#include "../types/SecondaryOrderId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/CumQty.hpp"
#include "../types/Account.hpp"
#include "../types/ExecId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MarketSegmentReceivedTime.hpp"
#include "../types/OrderId.hpp"
#include "../types/Origclordid.hpp"
#include "../types/TradeDate.hpp"
#include "../types/WorkingIndicator.hpp"
#include "../types/ExecRestatementReason.hpp"
#include "../types/Offset100Padding4.hpp"
#include "../types/MassActionReportIdOptional.hpp"
#include "../types/Ordtype.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/ExpireDate.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/StopPx.hpp"
#include "../types/MinQty.hpp"
#include "../types/MaxFloor.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;


#pragma pack(push, 1)

// Execution Report Cancel Message
struct execution_report_cancel_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::side side;
        sbe_binaryentrypoint::ord_status ord_status;
        sbe_binaryentrypoint::clordid clordid;
        sbe_binaryentrypoint::secondary_order_id secondary_order_id;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::cum_qty cum_qty;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::exec_id exec_id;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::market_segment_received_time market_segment_received_time;
        sbe_binaryentrypoint::order_id order_id;
        sbe_binaryentrypoint::origclordid origclordid;
        sbe_binaryentrypoint::trade_date trade_date;
        sbe_binaryentrypoint::working_indicator working_indicator;
        sbe_binaryentrypoint::exec_restatement_reason exec_restatement_reason;
        sbe_binaryentrypoint::offset_100_padding_4 offset_100_padding_4;
        sbe_binaryentrypoint::mass_action_report_id_optional mass_action_report_id_optional;
        sbe_binaryentrypoint::ordtype ordtype;
        sbe_binaryentrypoint::time_in_force time_in_force;
        sbe_binaryentrypoint::expire_date expire_date;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::price_optional price_optional;
        sbe_binaryentrypoint::stop_px stop_px;
        sbe_binaryentrypoint::min_qty min_qty;
        sbe_binaryentrypoint::max_floor max_floor;
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
    static execution_report_cancel_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_report_cancel_message*>(buffer);
    }

    // parse method const
    static const execution_report_cancel_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_report_cancel_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_report_cancel_message::fields_type, outbound_business_header) == 0, "unexpected offset of execution_report_cancel_message::fields_type::outbound_business_header");
static_assert(offsetof(execution_report_cancel_message::fields_type, side) == 18, "unexpected offset of execution_report_cancel_message::fields_type::side");
static_assert(offsetof(execution_report_cancel_message::fields_type, ord_status) == 19, "unexpected offset of execution_report_cancel_message::fields_type::ord_status");
static_assert(offsetof(execution_report_cancel_message::fields_type, clordid) == 20, "unexpected offset of execution_report_cancel_message::fields_type::clordid");
static_assert(offsetof(execution_report_cancel_message::fields_type, secondary_order_id) == 28, "unexpected offset of execution_report_cancel_message::fields_type::secondary_order_id");
static_assert(offsetof(execution_report_cancel_message::fields_type, security_id) == 36, "unexpected offset of execution_report_cancel_message::fields_type::security_id");
static_assert(offsetof(execution_report_cancel_message::fields_type, cum_qty) == 44, "unexpected offset of execution_report_cancel_message::fields_type::cum_qty");
static_assert(offsetof(execution_report_cancel_message::fields_type, account) == 52, "unexpected offset of execution_report_cancel_message::fields_type::account");
static_assert(offsetof(execution_report_cancel_message::fields_type, exec_id) == 56, "unexpected offset of execution_report_cancel_message::fields_type::exec_id");
static_assert(offsetof(execution_report_cancel_message::fields_type, transact_time) == 64, "unexpected offset of execution_report_cancel_message::fields_type::transact_time");
static_assert(offsetof(execution_report_cancel_message::fields_type, market_segment_received_time) == 72, "unexpected offset of execution_report_cancel_message::fields_type::market_segment_received_time");
static_assert(offsetof(execution_report_cancel_message::fields_type, order_id) == 80, "unexpected offset of execution_report_cancel_message::fields_type::order_id");
static_assert(offsetof(execution_report_cancel_message::fields_type, origclordid) == 88, "unexpected offset of execution_report_cancel_message::fields_type::origclordid");
static_assert(offsetof(execution_report_cancel_message::fields_type, trade_date) == 96, "unexpected offset of execution_report_cancel_message::fields_type::trade_date");
static_assert(offsetof(execution_report_cancel_message::fields_type, working_indicator) == 98, "unexpected offset of execution_report_cancel_message::fields_type::working_indicator");
static_assert(offsetof(execution_report_cancel_message::fields_type, exec_restatement_reason) == 99, "unexpected offset of execution_report_cancel_message::fields_type::exec_restatement_reason");
static_assert(offsetof(execution_report_cancel_message::fields_type, offset_100_padding_4) == 100, "unexpected offset of execution_report_cancel_message::fields_type::offset_100_padding_4");
static_assert(offsetof(execution_report_cancel_message::fields_type, mass_action_report_id_optional) == 104, "unexpected offset of execution_report_cancel_message::fields_type::mass_action_report_id_optional");
static_assert(offsetof(execution_report_cancel_message::fields_type, ordtype) == 112, "unexpected offset of execution_report_cancel_message::fields_type::ordtype");
static_assert(offsetof(execution_report_cancel_message::fields_type, time_in_force) == 113, "unexpected offset of execution_report_cancel_message::fields_type::time_in_force");
static_assert(offsetof(execution_report_cancel_message::fields_type, expire_date) == 114, "unexpected offset of execution_report_cancel_message::fields_type::expire_date");
static_assert(offsetof(execution_report_cancel_message::fields_type, order_qty) == 116, "unexpected offset of execution_report_cancel_message::fields_type::order_qty");
static_assert(offsetof(execution_report_cancel_message::fields_type, price_optional) == 124, "unexpected offset of execution_report_cancel_message::fields_type::price_optional");
static_assert(offsetof(execution_report_cancel_message::fields_type, stop_px) == 132, "unexpected offset of execution_report_cancel_message::fields_type::stop_px");
static_assert(offsetof(execution_report_cancel_message::fields_type, min_qty) == 140, "unexpected offset of execution_report_cancel_message::fields_type::min_qty");
static_assert(offsetof(execution_report_cancel_message::fields_type, max_floor) == 148, "unexpected offset of execution_report_cancel_message::fields_type::max_floor");
static_assert(sizeof(execution_report_cancel_message::fields_type) == 156, "unexpected sizeof execution_report_cancel_message::fields_type");

#pragma pack(pop)
}

#include "details/ExecutionReportCancelMessageWriter.hpp"
#include "details/ExecutionReportCancelMessageReader.hpp"
