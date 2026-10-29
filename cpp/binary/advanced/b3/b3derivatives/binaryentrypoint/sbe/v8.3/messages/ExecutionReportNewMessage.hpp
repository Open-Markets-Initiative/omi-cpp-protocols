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
#include "../types/OrderId.hpp"
#include "../types/Account.hpp"
#include "../types/ExecId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MarketSegmentReceivedTime.hpp"
#include "../types/ProtectionPrice.hpp"
#include "../types/TradeDate.hpp"
#include "../types/WorkingIndicator.hpp"
#include "../types/MultiLegReportingType.hpp"
#include "../types/Ordtype.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/ExpireDate.hpp"
#include "../types/OrderQty.hpp"
#include "../types/PriceOptional.hpp"
#include "../types/StopPx.hpp"
#include "../types/MinQty.hpp"
#include "../types/MaxFloor.hpp"
#include "../types/CrossidOptional.hpp"
#include "../types/ReceivedTime.hpp"
#include "../types/Offset152Padding3.hpp"
#include "../types/Ordtagid.hpp"
#include "../structs/InvestorId.hpp"
#include "../types/CrossType.hpp"
#include "../types/CrossPrioritization.hpp"
#include "../types/MmProtectionResetOptional.hpp"
#include "../types/Offset167Padding1.hpp"
#include "../types/StrategyId.hpp"
#include "../types/TradingSubAccount.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_3;


#pragma pack(push, 1)

// Execution Report New Message
struct execution_report_new_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::side side;
        sbe_binaryentrypoint::ord_status ord_status;
        sbe_binaryentrypoint::clordid clordid;
        sbe_binaryentrypoint::secondary_order_id secondary_order_id;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::order_id order_id;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::exec_id exec_id;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::market_segment_received_time market_segment_received_time;
        sbe_binaryentrypoint::protection_price protection_price;
        sbe_binaryentrypoint::trade_date trade_date;
        sbe_binaryentrypoint::working_indicator working_indicator;
        sbe_binaryentrypoint::multi_leg_reporting_type multi_leg_reporting_type;
        sbe_binaryentrypoint::ordtype ordtype;
        sbe_binaryentrypoint::time_in_force time_in_force;
        sbe_binaryentrypoint::expire_date expire_date;
        sbe_binaryentrypoint::order_qty order_qty;
        sbe_binaryentrypoint::price_optional price_optional;
        sbe_binaryentrypoint::stop_px stop_px;
        sbe_binaryentrypoint::min_qty min_qty;
        sbe_binaryentrypoint::max_floor max_floor;
        sbe_binaryentrypoint::crossid_optional crossid_optional;
        sbe_binaryentrypoint::received_time received_time;
        sbe_binaryentrypoint::offset_152_padding_3 offset_152_padding_3;
        sbe_binaryentrypoint::ordtagid ordtagid;
        sbe_binaryentrypoint::investor_id investor_id;
        sbe_binaryentrypoint::cross_type cross_type;
        sbe_binaryentrypoint::cross_prioritization cross_prioritization;
        sbe_binaryentrypoint::mm_protection_reset_optional mm_protection_reset_optional;
        sbe_binaryentrypoint::offset_167_padding_1 offset_167_padding_1;
        sbe_binaryentrypoint::strategy_id strategy_id;
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
    static execution_report_new_message* parse(std::byte* buffer) {
        return reinterpret_cast<execution_report_new_message*>(buffer);
    }

    // parse method const
    static const execution_report_new_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const execution_report_new_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(execution_report_new_message::fields_type, outbound_business_header) == 0, "unexpected offset of execution_report_new_message::fields_type::outbound_business_header");
static_assert(offsetof(execution_report_new_message::fields_type, side) == 18, "unexpected offset of execution_report_new_message::fields_type::side");
static_assert(offsetof(execution_report_new_message::fields_type, ord_status) == 19, "unexpected offset of execution_report_new_message::fields_type::ord_status");
static_assert(offsetof(execution_report_new_message::fields_type, clordid) == 20, "unexpected offset of execution_report_new_message::fields_type::clordid");
static_assert(offsetof(execution_report_new_message::fields_type, secondary_order_id) == 28, "unexpected offset of execution_report_new_message::fields_type::secondary_order_id");
static_assert(offsetof(execution_report_new_message::fields_type, security_id) == 36, "unexpected offset of execution_report_new_message::fields_type::security_id");
static_assert(offsetof(execution_report_new_message::fields_type, order_id) == 44, "unexpected offset of execution_report_new_message::fields_type::order_id");
static_assert(offsetof(execution_report_new_message::fields_type, account) == 52, "unexpected offset of execution_report_new_message::fields_type::account");
static_assert(offsetof(execution_report_new_message::fields_type, exec_id) == 56, "unexpected offset of execution_report_new_message::fields_type::exec_id");
static_assert(offsetof(execution_report_new_message::fields_type, transact_time) == 64, "unexpected offset of execution_report_new_message::fields_type::transact_time");
static_assert(offsetof(execution_report_new_message::fields_type, market_segment_received_time) == 72, "unexpected offset of execution_report_new_message::fields_type::market_segment_received_time");
static_assert(offsetof(execution_report_new_message::fields_type, protection_price) == 80, "unexpected offset of execution_report_new_message::fields_type::protection_price");
static_assert(offsetof(execution_report_new_message::fields_type, trade_date) == 88, "unexpected offset of execution_report_new_message::fields_type::trade_date");
static_assert(offsetof(execution_report_new_message::fields_type, working_indicator) == 90, "unexpected offset of execution_report_new_message::fields_type::working_indicator");
static_assert(offsetof(execution_report_new_message::fields_type, multi_leg_reporting_type) == 91, "unexpected offset of execution_report_new_message::fields_type::multi_leg_reporting_type");
static_assert(offsetof(execution_report_new_message::fields_type, ordtype) == 92, "unexpected offset of execution_report_new_message::fields_type::ordtype");
static_assert(offsetof(execution_report_new_message::fields_type, time_in_force) == 93, "unexpected offset of execution_report_new_message::fields_type::time_in_force");
static_assert(offsetof(execution_report_new_message::fields_type, expire_date) == 94, "unexpected offset of execution_report_new_message::fields_type::expire_date");
static_assert(offsetof(execution_report_new_message::fields_type, order_qty) == 96, "unexpected offset of execution_report_new_message::fields_type::order_qty");
static_assert(offsetof(execution_report_new_message::fields_type, price_optional) == 104, "unexpected offset of execution_report_new_message::fields_type::price_optional");
static_assert(offsetof(execution_report_new_message::fields_type, stop_px) == 112, "unexpected offset of execution_report_new_message::fields_type::stop_px");
static_assert(offsetof(execution_report_new_message::fields_type, min_qty) == 120, "unexpected offset of execution_report_new_message::fields_type::min_qty");
static_assert(offsetof(execution_report_new_message::fields_type, max_floor) == 128, "unexpected offset of execution_report_new_message::fields_type::max_floor");
static_assert(offsetof(execution_report_new_message::fields_type, crossid_optional) == 136, "unexpected offset of execution_report_new_message::fields_type::crossid_optional");
static_assert(offsetof(execution_report_new_message::fields_type, received_time) == 144, "unexpected offset of execution_report_new_message::fields_type::received_time");
static_assert(offsetof(execution_report_new_message::fields_type, offset_152_padding_3) == 152, "unexpected offset of execution_report_new_message::fields_type::offset_152_padding_3");
static_assert(offsetof(execution_report_new_message::fields_type, ordtagid) == 155, "unexpected offset of execution_report_new_message::fields_type::ordtagid");
static_assert(offsetof(execution_report_new_message::fields_type, investor_id) == 156, "unexpected offset of execution_report_new_message::fields_type::investor_id");
static_assert(offsetof(execution_report_new_message::fields_type, cross_type) == 164, "unexpected offset of execution_report_new_message::fields_type::cross_type");
static_assert(offsetof(execution_report_new_message::fields_type, cross_prioritization) == 165, "unexpected offset of execution_report_new_message::fields_type::cross_prioritization");
static_assert(offsetof(execution_report_new_message::fields_type, mm_protection_reset_optional) == 166, "unexpected offset of execution_report_new_message::fields_type::mm_protection_reset_optional");
static_assert(offsetof(execution_report_new_message::fields_type, offset_167_padding_1) == 167, "unexpected offset of execution_report_new_message::fields_type::offset_167_padding_1");
static_assert(offsetof(execution_report_new_message::fields_type, strategy_id) == 168, "unexpected offset of execution_report_new_message::fields_type::strategy_id");
static_assert(offsetof(execution_report_new_message::fields_type, trading_sub_account) == 172, "unexpected offset of execution_report_new_message::fields_type::trading_sub_account");
static_assert(sizeof(execution_report_new_message::fields_type) == 176, "unexpected sizeof execution_report_new_message::fields_type");

#pragma pack(pop)
}

#include "details/ExecutionReportNewMessageWriter.hpp"
#include "details/ExecutionReportNewMessageReader.hpp"
