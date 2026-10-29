#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/MassActionType.hpp"
#include "../types/MassActionScope.hpp"
#include "../types/Clordid.hpp"
#include "../types/MassActionReportId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/MassActionResponse.hpp"
#include "../types/MassActionRejectReason.hpp"
#include "../types/MassCancelRestatementReason.hpp"
#include "../types/Ordtagid.hpp"
#include "../types/SideOptional.hpp"
#include "../types/Offset49Padding1.hpp"
#include "../types/Asset.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;


#pragma pack(push, 1)

// Order Mass Action Report Message
struct order_mass_action_report_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::mass_action_type mass_action_type;
        sbe_binaryentrypoint::mass_action_scope mass_action_scope;
        sbe_binaryentrypoint::clordid clordid;
        sbe_binaryentrypoint::mass_action_report_id mass_action_report_id;
        sbe_binaryentrypoint::transact_time transact_time;
        sbe_binaryentrypoint::mass_action_response mass_action_response;
        sbe_binaryentrypoint::mass_action_reject_reason mass_action_reject_reason;
        sbe_binaryentrypoint::mass_cancel_restatement_reason mass_cancel_restatement_reason;
        sbe_binaryentrypoint::ordtagid ordtagid;
        sbe_binaryentrypoint::side_optional side_optional;
        sbe_binaryentrypoint::offset_49_padding_1 offset_49_padding_1;
        sbe_binaryentrypoint::asset asset;
        sbe_binaryentrypoint::security_id_optional security_id_optional;
        sbe_binaryentrypoint::investor_id investor_id;
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
    sbe_var_data text() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static order_mass_action_report_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_mass_action_report_message*>(buffer);
    }

    // parse method const
    static const order_mass_action_report_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_mass_action_report_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_mass_action_report_message::fields_type, outbound_business_header) == 0, "unexpected offset of order_mass_action_report_message::fields_type::outbound_business_header");
static_assert(offsetof(order_mass_action_report_message::fields_type, mass_action_type) == 18, "unexpected offset of order_mass_action_report_message::fields_type::mass_action_type");
static_assert(offsetof(order_mass_action_report_message::fields_type, mass_action_scope) == 19, "unexpected offset of order_mass_action_report_message::fields_type::mass_action_scope");
static_assert(offsetof(order_mass_action_report_message::fields_type, clordid) == 20, "unexpected offset of order_mass_action_report_message::fields_type::clordid");
static_assert(offsetof(order_mass_action_report_message::fields_type, mass_action_report_id) == 28, "unexpected offset of order_mass_action_report_message::fields_type::mass_action_report_id");
static_assert(offsetof(order_mass_action_report_message::fields_type, transact_time) == 36, "unexpected offset of order_mass_action_report_message::fields_type::transact_time");
static_assert(offsetof(order_mass_action_report_message::fields_type, mass_action_response) == 44, "unexpected offset of order_mass_action_report_message::fields_type::mass_action_response");
static_assert(offsetof(order_mass_action_report_message::fields_type, mass_action_reject_reason) == 45, "unexpected offset of order_mass_action_report_message::fields_type::mass_action_reject_reason");
static_assert(offsetof(order_mass_action_report_message::fields_type, mass_cancel_restatement_reason) == 46, "unexpected offset of order_mass_action_report_message::fields_type::mass_cancel_restatement_reason");
static_assert(offsetof(order_mass_action_report_message::fields_type, ordtagid) == 47, "unexpected offset of order_mass_action_report_message::fields_type::ordtagid");
static_assert(offsetof(order_mass_action_report_message::fields_type, side_optional) == 48, "unexpected offset of order_mass_action_report_message::fields_type::side_optional");
static_assert(offsetof(order_mass_action_report_message::fields_type, offset_49_padding_1) == 49, "unexpected offset of order_mass_action_report_message::fields_type::offset_49_padding_1");
static_assert(offsetof(order_mass_action_report_message::fields_type, asset) == 50, "unexpected offset of order_mass_action_report_message::fields_type::asset");
static_assert(offsetof(order_mass_action_report_message::fields_type, security_id_optional) == 56, "unexpected offset of order_mass_action_report_message::fields_type::security_id_optional");
static_assert(offsetof(order_mass_action_report_message::fields_type, investor_id) == 64, "unexpected offset of order_mass_action_report_message::fields_type::investor_id");
static_assert(sizeof(order_mass_action_report_message::fields_type) == 72, "unexpected sizeof order_mass_action_report_message::fields_type");

#pragma pack(pop)
}

#include "details/OrderMassActionReportMessageWriter.hpp"
#include "details/OrderMassActionReportMessageReader.hpp"
