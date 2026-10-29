#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/AllocId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/AllocReportId.hpp"
#include "../types/AllocTransType.hpp"
#include "../types/AllocReportType.hpp"
#include "../types/AllocNoOrdersType.hpp"
#include "../types/AllocRejCode.hpp"
#include "../types/Quantity.hpp"
#include "../types/AllocStatus.hpp"
#include "../types/TradeDateOptional.hpp"
#include "../types/TransactTime.hpp"
#include "../types/Side.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

// Allocation Report Message
struct allocation_report_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::alloc_id alloc_id;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::alloc_report_id alloc_report_id;
        sbe_binaryentrypoint::alloc_trans_type alloc_trans_type;
        sbe_binaryentrypoint::alloc_report_type alloc_report_type;
        sbe_binaryentrypoint::alloc_no_orders_type alloc_no_orders_type;
        sbe_binaryentrypoint::alloc_rej_code alloc_rej_code;
        sbe_binaryentrypoint::quantity quantity;
        sbe_binaryentrypoint::alloc_status alloc_status;
        sbe_binaryentrypoint::trade_date_optional trade_date_optional;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::side side;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static allocation_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<allocation_report_message*>(buffer);
    }

    // parse method const
    static const allocation_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const allocation_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(allocation_report_message::fields_type, outbound_business_header) == 0, "unexpected offset of allocation_report_message::fields_type::outbound_business_header");
static_assert(offsetof(allocation_report_message::fields_type, alloc_id) == 18, "unexpected offset of allocation_report_message::fields_type::alloc_id");
static_assert(offsetof(allocation_report_message::fields_type, security_id) == 26, "unexpected offset of allocation_report_message::fields_type::security_id");
static_assert(offsetof(allocation_report_message::fields_type, alloc_report_id) == 34, "unexpected offset of allocation_report_message::fields_type::alloc_report_id");
static_assert(offsetof(allocation_report_message::fields_type, alloc_trans_type) == 42, "unexpected offset of allocation_report_message::fields_type::alloc_trans_type");
static_assert(offsetof(allocation_report_message::fields_type, alloc_report_type) == 43, "unexpected offset of allocation_report_message::fields_type::alloc_report_type");
static_assert(offsetof(allocation_report_message::fields_type, alloc_no_orders_type) == 44, "unexpected offset of allocation_report_message::fields_type::alloc_no_orders_type");
static_assert(offsetof(allocation_report_message::fields_type, alloc_rej_code) == 45, "unexpected offset of allocation_report_message::fields_type::alloc_rej_code");
static_assert(offsetof(allocation_report_message::fields_type, quantity) == 49, "unexpected offset of allocation_report_message::fields_type::quantity");
static_assert(offsetof(allocation_report_message::fields_type, alloc_status) == 57, "unexpected offset of allocation_report_message::fields_type::alloc_status");
static_assert(offsetof(allocation_report_message::fields_type, trade_date_optional) == 58, "unexpected offset of allocation_report_message::fields_type::trade_date_optional");
static_assert(offsetof(allocation_report_message::fields_type, transact_time) == 60, "unexpected offset of allocation_report_message::fields_type::transact_time");
static_assert(offsetof(allocation_report_message::fields_type, side) == 68, "unexpected offset of allocation_report_message::fields_type::side");
static_assert(offsetof(allocation_report_message::fields_type, sender_location) == 69, "unexpected offset of allocation_report_message::fields_type::sender_location");
static_assert(offsetof(allocation_report_message::fields_type, entering_trader) == 79, "unexpected offset of allocation_report_message::fields_type::entering_trader");
static_assert(sizeof(allocation_report_message::fields_type) == 84, "unexpected sizeof allocation_report_message::fields_type");
static_assert(sizeof(allocation_report_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 84, "unexpected sizeof allocation_report_message");

#pragma pack(pop)
}
