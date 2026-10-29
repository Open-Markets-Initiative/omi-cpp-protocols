#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../types/MassActionType.hpp"
#include "../types/MassActionScope.hpp"
#include "../types/Clordid.hpp"
#include "../types/MassCancelRestatementReason.hpp"
#include "../types/Ordtagid.hpp"
#include "../types/SideOptional.hpp"
#include "../types/Offset31Padding1.hpp"
#include "../types/Asset.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../structs/InvestorId.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)

// Order Mass Action Request Message
struct order_mass_action_request_message {

    struct fields_type {
        sbe_binaryentrypoint::inbound_business_header inbound_business_header;
        sbe_binaryentrypoint::mass_action_type mass_action_type;
        sbe_binaryentrypoint::mass_action_scope mass_action_scope;
        sbe_binaryentrypoint::clordid clordid;
        sbe_binaryentrypoint::mass_cancel_restatement_reason mass_cancel_restatement_reason;
        sbe_binaryentrypoint::ordtagid ordtagid;
        sbe_binaryentrypoint::side_optional side_optional;
        sbe_binaryentrypoint::offset_31_padding_1 offset_31_padding_1;
        sbe_binaryentrypoint::asset asset;
        sbe_binaryentrypoint::security_id_optional security_id_optional;
        sbe_binaryentrypoint::investor_id investor_id;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static order_mass_action_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_mass_action_request_message*>(buffer);
    }

    // parse method const
    static const order_mass_action_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_mass_action_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_mass_action_request_message::fields_type, inbound_business_header) == 0, "unexpected offset of order_mass_action_request_message::fields_type::inbound_business_header");
static_assert(offsetof(order_mass_action_request_message::fields_type, mass_action_type) == 18, "unexpected offset of order_mass_action_request_message::fields_type::mass_action_type");
static_assert(offsetof(order_mass_action_request_message::fields_type, mass_action_scope) == 19, "unexpected offset of order_mass_action_request_message::fields_type::mass_action_scope");
static_assert(offsetof(order_mass_action_request_message::fields_type, clordid) == 20, "unexpected offset of order_mass_action_request_message::fields_type::clordid");
static_assert(offsetof(order_mass_action_request_message::fields_type, mass_cancel_restatement_reason) == 28, "unexpected offset of order_mass_action_request_message::fields_type::mass_cancel_restatement_reason");
static_assert(offsetof(order_mass_action_request_message::fields_type, ordtagid) == 29, "unexpected offset of order_mass_action_request_message::fields_type::ordtagid");
static_assert(offsetof(order_mass_action_request_message::fields_type, side_optional) == 30, "unexpected offset of order_mass_action_request_message::fields_type::side_optional");
static_assert(offsetof(order_mass_action_request_message::fields_type, offset_31_padding_1) == 31, "unexpected offset of order_mass_action_request_message::fields_type::offset_31_padding_1");
static_assert(offsetof(order_mass_action_request_message::fields_type, asset) == 32, "unexpected offset of order_mass_action_request_message::fields_type::asset");
static_assert(offsetof(order_mass_action_request_message::fields_type, security_id_optional) == 38, "unexpected offset of order_mass_action_request_message::fields_type::security_id_optional");
static_assert(offsetof(order_mass_action_request_message::fields_type, investor_id) == 46, "unexpected offset of order_mass_action_request_message::fields_type::investor_id");
static_assert(sizeof(order_mass_action_request_message::fields_type) == 54, "unexpected sizeof order_mass_action_request_message::fields_type");
static_assert(sizeof(order_mass_action_request_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 54, "unexpected sizeof order_mass_action_request_message");

#pragma pack(pop)
}
