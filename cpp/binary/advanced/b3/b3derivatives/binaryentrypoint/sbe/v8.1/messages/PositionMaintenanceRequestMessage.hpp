#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../types/PosReqId.hpp"
#include "../types/SecurityId.hpp"
#include "../types/ThresholdAmount.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/PosTransType.hpp"
#include "../types/ClearingBusinessDate.hpp"
#include "../types/ContraryInstructionIndicator.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/LongQty.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


#pragma pack(push, 1)

// Position Maintenance Request Message
struct position_maintenance_request_message {

    struct fields_type {
        sbe_binaryentrypoint::inbound_business_header inbound_business_header;
        sbe_binaryentrypoint::pos_req_id pos_req_id;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::threshold_amount threshold_amount;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::pos_trans_type pos_trans_type;
        sbe_binaryentrypoint::clearing_business_date clearing_business_date;
        sbe_binaryentrypoint::contrary_instruction_indicator contrary_instruction_indicator;
        sbe_binaryentrypoint::entering_trader entering_trader;
        sbe_binaryentrypoint::long_qty long_qty;
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
    static position_maintenance_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<position_maintenance_request_message*>(buffer);
    }

    // parse method const
    static const position_maintenance_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const position_maintenance_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(position_maintenance_request_message::fields_type, inbound_business_header) == 0, "unexpected offset of position_maintenance_request_message::fields_type::inbound_business_header");
static_assert(offsetof(position_maintenance_request_message::fields_type, pos_req_id) == 18, "unexpected offset of position_maintenance_request_message::fields_type::pos_req_id");
static_assert(offsetof(position_maintenance_request_message::fields_type, security_id) == 26, "unexpected offset of position_maintenance_request_message::fields_type::security_id");
static_assert(offsetof(position_maintenance_request_message::fields_type, threshold_amount) == 34, "unexpected offset of position_maintenance_request_message::fields_type::threshold_amount");
static_assert(offsetof(position_maintenance_request_message::fields_type, account) == 42, "unexpected offset of position_maintenance_request_message::fields_type::account");
static_assert(offsetof(position_maintenance_request_message::fields_type, sender_location) == 46, "unexpected offset of position_maintenance_request_message::fields_type::sender_location");
static_assert(offsetof(position_maintenance_request_message::fields_type, pos_trans_type) == 56, "unexpected offset of position_maintenance_request_message::fields_type::pos_trans_type");
static_assert(offsetof(position_maintenance_request_message::fields_type, clearing_business_date) == 57, "unexpected offset of position_maintenance_request_message::fields_type::clearing_business_date");
static_assert(offsetof(position_maintenance_request_message::fields_type, contrary_instruction_indicator) == 59, "unexpected offset of position_maintenance_request_message::fields_type::contrary_instruction_indicator");
static_assert(offsetof(position_maintenance_request_message::fields_type, entering_trader) == 60, "unexpected offset of position_maintenance_request_message::fields_type::entering_trader");
static_assert(offsetof(position_maintenance_request_message::fields_type, long_qty) == 65, "unexpected offset of position_maintenance_request_message::fields_type::long_qty");
static_assert(sizeof(position_maintenance_request_message::fields_type) == 73, "unexpected sizeof position_maintenance_request_message::fields_type");

#pragma pack(pop)
}

#include "details/PositionMaintenanceRequestMessageWriter.hpp"
#include "details/PositionMaintenanceRequestMessageReader.hpp"
