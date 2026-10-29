#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../types/PosReqId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrigPosReqRefId.hpp"
#include "../types/PosMaintRptRefId.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

// Position Maintenance Cancel Request Message
struct position_maintenance_cancel_request_message {

    struct fields_type {
        sbe_binaryentrypoint::inbound_business_header inbound_business_header;
        sbe_binaryentrypoint::pos_req_id pos_req_id;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::orig_pos_req_ref_id orig_pos_req_ref_id;
        sbe_binaryentrypoint::pos_maint_rpt_ref_id pos_maint_rpt_ref_id;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static position_maintenance_cancel_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<position_maintenance_cancel_request_message*>(buffer);
    }

    // parse method const
    static const position_maintenance_cancel_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const position_maintenance_cancel_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(position_maintenance_cancel_request_message::fields_type, inbound_business_header) == 0, "unexpected offset of position_maintenance_cancel_request_message::fields_type::inbound_business_header");
static_assert(offsetof(position_maintenance_cancel_request_message::fields_type, pos_req_id) == 18, "unexpected offset of position_maintenance_cancel_request_message::fields_type::pos_req_id");
static_assert(offsetof(position_maintenance_cancel_request_message::fields_type, security_id) == 26, "unexpected offset of position_maintenance_cancel_request_message::fields_type::security_id");
static_assert(offsetof(position_maintenance_cancel_request_message::fields_type, orig_pos_req_ref_id) == 34, "unexpected offset of position_maintenance_cancel_request_message::fields_type::orig_pos_req_ref_id");
static_assert(offsetof(position_maintenance_cancel_request_message::fields_type, pos_maint_rpt_ref_id) == 42, "unexpected offset of position_maintenance_cancel_request_message::fields_type::pos_maint_rpt_ref_id");
static_assert(offsetof(position_maintenance_cancel_request_message::fields_type, sender_location) == 50, "unexpected offset of position_maintenance_cancel_request_message::fields_type::sender_location");
static_assert(offsetof(position_maintenance_cancel_request_message::fields_type, entering_trader) == 60, "unexpected offset of position_maintenance_cancel_request_message::fields_type::entering_trader");
static_assert(sizeof(position_maintenance_cancel_request_message::fields_type) == 65, "unexpected sizeof position_maintenance_cancel_request_message::fields_type");
static_assert(sizeof(position_maintenance_cancel_request_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 65, "unexpected sizeof position_maintenance_cancel_request_message");

#pragma pack(pop)
}
