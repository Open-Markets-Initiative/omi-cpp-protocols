#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/OutboundBusinessHeader.hpp"
#include "../types/Offset18Padding2.hpp"
#include "../types/SecurityReqId.hpp"
#include "../types/SecurityIdOptional.hpp"
#include "../types/SecurityResponseType.hpp"
#include "../types/SecurityStrategyType.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityResponseId.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_1;

#pragma pack(push, 1)

// Security Definition Response Message
struct security_definition_response_message {

    struct fields_type {
        sbe_binaryentrypoint::outbound_business_header outbound_business_header;
        sbe_binaryentrypoint::offset_18_padding_2 offset_18_padding_2;
        sbe_binaryentrypoint::security_req_id security_req_id;
        sbe_binaryentrypoint::security_id_optional security_id_optional;
        sbe_binaryentrypoint::security_response_type security_response_type;
        sbe_binaryentrypoint::security_strategy_type security_strategy_type;
        sbe_binaryentrypoint::symbol symbol;
        sbe_binaryentrypoint::security_response_id security_response_id;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
    };

    sbe_binaryentrypoint::simple_open_framing_header header = {std::uint16_t(sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(fields_type) + sizeof(sbe_binaryentrypoint::message_header)), encoding_type(60240)};
    sbe_binaryentrypoint::message_header message_header;

    fields_type fields;

    // parse method
    static security_definition_response_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_definition_response_message*>(buffer);
    }

    // parse method const
    static const security_definition_response_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_definition_response_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_definition_response_message::fields_type, outbound_business_header) == 0, "unexpected offset of security_definition_response_message::fields_type::outbound_business_header");
static_assert(offsetof(security_definition_response_message::fields_type, offset_18_padding_2) == 18, "unexpected offset of security_definition_response_message::fields_type::offset_18_padding_2");
static_assert(offsetof(security_definition_response_message::fields_type, security_req_id) == 20, "unexpected offset of security_definition_response_message::fields_type::security_req_id");
static_assert(offsetof(security_definition_response_message::fields_type, security_id_optional) == 28, "unexpected offset of security_definition_response_message::fields_type::security_id_optional");
static_assert(offsetof(security_definition_response_message::fields_type, security_response_type) == 36, "unexpected offset of security_definition_response_message::fields_type::security_response_type");
static_assert(offsetof(security_definition_response_message::fields_type, security_strategy_type) == 37, "unexpected offset of security_definition_response_message::fields_type::security_strategy_type");
static_assert(offsetof(security_definition_response_message::fields_type, symbol) == 40, "unexpected offset of security_definition_response_message::fields_type::symbol");
static_assert(offsetof(security_definition_response_message::fields_type, security_response_id) == 60, "unexpected offset of security_definition_response_message::fields_type::security_response_id");
static_assert(offsetof(security_definition_response_message::fields_type, sender_location) == 68, "unexpected offset of security_definition_response_message::fields_type::sender_location");
static_assert(offsetof(security_definition_response_message::fields_type, entering_trader) == 78, "unexpected offset of security_definition_response_message::fields_type::entering_trader");
static_assert(sizeof(security_definition_response_message::fields_type) == 83, "unexpected sizeof security_definition_response_message::fields_type");
static_assert(sizeof(security_definition_response_message) == sizeof(sbe_binaryentrypoint::simple_open_framing_header) + sizeof(sbe_binaryentrypoint::message_header) + 83, "unexpected sizeof security_definition_response_message");

#pragma pack(pop)
}
