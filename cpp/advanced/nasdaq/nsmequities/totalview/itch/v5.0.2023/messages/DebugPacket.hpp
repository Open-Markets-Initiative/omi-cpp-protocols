#pragma once

#include <cstddef>
#include "../structs/ClientPacketHeader.hpp"
#include "../types/Text.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;

#pragma pack(push, 1)

// Debug Packet
struct debug_packet {

    struct fields_type {
        itch_totalview::text text;
    };

    client_packet_header header = {std::uint16_t(sizeof(client_packet_header) + sizeof(fields_type) - 2), client_packet_type::enum_type::debug_packet};

    fields_type fields;

    // parse method
    static debug_packet* parse(std::byte* buffer) {
        return reinterpret_cast<debug_packet*>(buffer);
    }

    // parse method const
    static const debug_packet* parse(const std::byte* buffer) {
        return reinterpret_cast<const debug_packet*>(buffer);
    }

};

// layout verification
static_assert(offsetof(debug_packet::fields_type, text) == 0, "unexpected offset of debug_packet::fields_type::text");
static_assert(sizeof(debug_packet::fields_type) == 1, "unexpected sizeof debug_packet::fields_type");
static_assert(sizeof(debug_packet) == sizeof(client_packet_header) + 1, "unexpected sizeof debug_packet");

#pragma pack(pop)
}
