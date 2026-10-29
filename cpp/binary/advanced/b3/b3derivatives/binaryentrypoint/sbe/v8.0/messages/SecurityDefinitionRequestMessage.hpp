#pragma once

#include <cstddef>
#include "../structs/SimpleOpenFramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../structs/InboundBusinessHeader.hpp"
#include "../types/SecurityReqId.hpp"
#include "../types/SenderLocation.hpp"
#include "../types/EnteringTrader.hpp"
#include "../types/LegSymbol.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSide.hpp"
#include "../types/Padding1.hpp"
#include "../structs/GroupSizeEncoding.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

namespace sbe_binaryentrypoint = ::b3::b3derivatives::binaryentrypoint::sbe::v8_0;

#pragma pack(push, 1)
struct security_definition_request_message_legs_groups_entry {
    sbe_binaryentrypoint::leg_symbol leg_symbol;
    sbe_binaryentrypoint::leg_ratio_qty leg_ratio_qty;
    sbe_binaryentrypoint::leg_side leg_side;
    sbe_binaryentrypoint::padding_1 padding_1;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Security Definition Request Message
struct security_definition_request_message {

    struct fields_type {
        sbe_binaryentrypoint::inbound_business_header inbound_business_header;
        sbe_binaryentrypoint::security_req_id security_req_id;
        sbe_binaryentrypoint::sender_location sender_location;
        sbe_binaryentrypoint::entering_trader entering_trader;
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
    sbe_group_iterator<security_definition_request_message_legs_groups_entry, group_size_encoding> legs_groups() const {
        return { tail_begin(), tail_end() };
    }


    // parse method
    static security_definition_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<security_definition_request_message*>(buffer);
    }

    // parse method const
    static const security_definition_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const security_definition_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(security_definition_request_message::fields_type, inbound_business_header) == 0, "unexpected offset of security_definition_request_message::fields_type::inbound_business_header");
static_assert(offsetof(security_definition_request_message::fields_type, security_req_id) == 18, "unexpected offset of security_definition_request_message::fields_type::security_req_id");
static_assert(offsetof(security_definition_request_message::fields_type, sender_location) == 26, "unexpected offset of security_definition_request_message::fields_type::sender_location");
static_assert(offsetof(security_definition_request_message::fields_type, entering_trader) == 36, "unexpected offset of security_definition_request_message::fields_type::entering_trader");
static_assert(sizeof(security_definition_request_message::fields_type) == 41, "unexpected sizeof security_definition_request_message::fields_type");

#pragma pack(pop)
}

#include "details/SecurityDefinitionRequestMessageWriter.hpp"
#include "details/SecurityDefinitionRequestMessageReader.hpp"
