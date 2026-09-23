#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../types/RejectReasonCode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Login Rejected Packet
struct login_rejected_packet {

    struct fields_type {
        itch_totalview::reject_reason_code reject_reason_code;
    };

    server_packet_header header = {std::uint16_t(sizeof(server_packet_header) + sizeof(fields_type) - 2), server_packet_type::enum_type::login_rejected_packet};

    fields_type fields;

    // parse method
    static login_rejected_packet* parse(std::byte* buffer) {
        return reinterpret_cast<login_rejected_packet*>(buffer);
    }

    // parse method const
    static const login_rejected_packet* parse(const std::byte* buffer) {
        return reinterpret_cast<const login_rejected_packet*>(buffer);
    }

};

// layout verification
static_assert(offsetof(login_rejected_packet::fields_type, reject_reason_code) == 0, "unexpected offset of login_rejected_packet::fields_type::reject_reason_code");
static_assert(sizeof(login_rejected_packet::fields_type) == 1, "unexpected sizeof login_rejected_packet::fields_type");
static_assert(sizeof(login_rejected_packet) == sizeof(server_packet_header) + 1, "unexpected sizeof login_rejected_packet");

#pragma pack(pop)
}
