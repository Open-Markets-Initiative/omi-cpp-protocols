#pragma once

#include <cstddef>
#include "../structs/EsesmPacketHeader.hpp"
#include "../types/RefreshMessageType.hpp"
#include "../types/UnsequencedMessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

#pragma pack(push, 1)

// Refresh Request Message
struct refresh_request_message {

    struct fields_type {
        mach_depthofmarket::refresh_message_type refresh_message_type;
    };

    mach_depthofmarket::esesm_packet_header header = {std::uint16_t(sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(fields_type) + sizeof(mach_depthofmarket::unsequenced_message_type) - 2), esesm_packet_type::enum_type::unsequenced_data_packet};
    mach_depthofmarket::unsequenced_message_type unsequenced_message_type = mach_depthofmarket::unsequenced_message_type::enum_type::refresh_request_message;

    fields_type fields;

    // parse method
    static refresh_request_message* parse(std::byte* buffer) {
        return reinterpret_cast<refresh_request_message*>(buffer);
    }

    // parse method const
    static const refresh_request_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const refresh_request_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(refresh_request_message::fields_type, refresh_message_type) == 0, "unexpected offset of refresh_request_message::fields_type::refresh_message_type");
static_assert(sizeof(refresh_request_message::fields_type) == 1, "unexpected sizeof refresh_request_message::fields_type");
static_assert(sizeof(refresh_request_message) == sizeof(mach_depthofmarket::esesm_packet_header) + sizeof(mach_depthofmarket::unsequenced_message_type) + 1, "unexpected sizeof refresh_request_message");

#pragma pack(pop)
}
