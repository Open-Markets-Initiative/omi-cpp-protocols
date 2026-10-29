#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/PosReqIdOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/PosMaintRptId.hpp"
#include "../types/PosTransType.hpp"
#include "../types/PosMaintAction.hpp"
#include "../types/PosMaintStatus.hpp"
#include "../types/TradeIdOptional.hpp"
#include "../types/OrigPosReqRefId.hpp"
#include "../types/AccountType.hpp"
#include "../types/ClearingBusinessDate.hpp"
#include "../types/ThresholdAmount.hpp"
#include "../types/TransactTime.hpp"
#include "../types/Account.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/PosMaintResult.hpp"
#include "../types/ContraryInstructionIndicator.hpp"
#include "../types/PosType.hpp"
#include "../types/LongQtyOptional.hpp"
#include "../types/ShortQty.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)
struct position_maintenance_report_message_positions_groups_entry {
    sbe_binaryentrypoint::pos_type pos_type;
    sbe_binaryentrypoint::long_qty_optional long_qty_optional;
    sbe_binaryentrypoint::short_qty short_qty;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Position Maintenance Report Message
struct position_maintenance_report_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::pos_req_id_optional pos_req_id_optional;
        sbe_binaryentrypoint::security_id security_id;
        sbe_binaryentrypoint::pos_maint_rpt_id pos_maint_rpt_id;
        sbe_binaryentrypoint::pos_trans_type pos_trans_type;
        sbe_binaryentrypoint::pos_maint_action pos_maint_action;
        sbe_binaryentrypoint::pos_maint_status pos_maint_status;
        sbe_binaryentrypoint::trade_id_optional trade_id_optional;
        sbe_binaryentrypoint::orig_pos_req_ref_id orig_pos_req_ref_id;
        sbe_binaryentrypoint::account_type account_type;
        sbe_binaryentrypoint::clearing_business_date clearing_business_date;
        sbe_binaryentrypoint::threshold_amount threshold_amount;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::account account;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::pos_maint_result pos_maint_result;
        sbe_binaryentrypoint::contrary_instruction_indicator contrary_instruction_indicator;
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
    sbe_group_iterator<position_maintenance_report_message_positions_groups_entry, group_size_encoding> positions_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_var_data desk_id(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data memo(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data text(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static position_maintenance_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<position_maintenance_report_message*>(buffer);
    }

    // parse method const
    static const position_maintenance_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const position_maintenance_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(position_maintenance_report_message::fields_type, outbound_business_header) == 0, "unexpected offset of position_maintenance_report_message::fields_type::outbound_business_header");
static_assert(offsetof(position_maintenance_report_message::fields_type, pos_req_id_optional) == 18, "unexpected offset of position_maintenance_report_message::fields_type::pos_req_id_optional");
static_assert(offsetof(position_maintenance_report_message::fields_type, security_id) == 26, "unexpected offset of position_maintenance_report_message::fields_type::security_id");
static_assert(offsetof(position_maintenance_report_message::fields_type, pos_maint_rpt_id) == 34, "unexpected offset of position_maintenance_report_message::fields_type::pos_maint_rpt_id");
static_assert(offsetof(position_maintenance_report_message::fields_type, pos_trans_type) == 42, "unexpected offset of position_maintenance_report_message::fields_type::pos_trans_type");
static_assert(offsetof(position_maintenance_report_message::fields_type, pos_maint_action) == 43, "unexpected offset of position_maintenance_report_message::fields_type::pos_maint_action");
static_assert(offsetof(position_maintenance_report_message::fields_type, pos_maint_status) == 44, "unexpected offset of position_maintenance_report_message::fields_type::pos_maint_status");
static_assert(offsetof(position_maintenance_report_message::fields_type, trade_id_optional) == 45, "unexpected offset of position_maintenance_report_message::fields_type::trade_id_optional");
static_assert(offsetof(position_maintenance_report_message::fields_type, orig_pos_req_ref_id) == 49, "unexpected offset of position_maintenance_report_message::fields_type::orig_pos_req_ref_id");
static_assert(offsetof(position_maintenance_report_message::fields_type, account_type) == 57, "unexpected offset of position_maintenance_report_message::fields_type::account_type");
static_assert(offsetof(position_maintenance_report_message::fields_type, clearing_business_date) == 58, "unexpected offset of position_maintenance_report_message::fields_type::clearing_business_date");
static_assert(offsetof(position_maintenance_report_message::fields_type, threshold_amount) == 60, "unexpected offset of position_maintenance_report_message::fields_type::threshold_amount");
static_assert(offsetof(position_maintenance_report_message::fields_type, transact_time) == 68, "unexpected offset of position_maintenance_report_message::fields_type::transact_time");
static_assert(offsetof(position_maintenance_report_message::fields_type, account) == 76, "unexpected offset of position_maintenance_report_message::fields_type::account");
static_assert(offsetof(position_maintenance_report_message::fields_type, sender_location) == 80, "unexpected offset of position_maintenance_report_message::fields_type::sender_location");
static_assert(offsetof(position_maintenance_report_message::fields_type, pos_maint_result) == 90, "unexpected offset of position_maintenance_report_message::fields_type::pos_maint_result");
static_assert(offsetof(position_maintenance_report_message::fields_type, contrary_instruction_indicator) == 94, "unexpected offset of position_maintenance_report_message::fields_type::contrary_instruction_indicator");
static_assert(sizeof(position_maintenance_report_message::fields_type) == 95, "unexpected sizeof position_maintenance_report_message::fields_type");

#pragma pack(pop)
}

#include "details/PositionMaintenanceReportMessageWriter.hpp"
#include "details/PositionMaintenanceReportMessageReader.hpp"
