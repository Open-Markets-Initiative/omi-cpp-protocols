#pragma once

#include <cstddef>
#include "../structs/ClientPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;


#pragma pack(push, 1)

// Debug Packet
struct debug_packet {

    struct fields_type {
    };

    itch_itto::client_packet_header header = {std::uint16_t(sizeof(itch_itto::client_packet_header) - 2), client_packet_type::enum_type::debug_packet};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(itch_itto::client_packet_header);

    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.packet_length.get().value();
        return (sz + 2) == sizeof(itch_itto::client_packet_header)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(itch_itto::client_packet_header));
    }

    // sequential access to variable-length regions
    external_var_data debug_text() const {
        return { tail_begin(), static_cast<std::size_t>(header.packet_length.get().value() - 1), tail_end() };
    }


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
static_assert(sizeof(debug_packet::fields_type) == 1, "unexpected sizeof debug_packet::fields_type");

#pragma pack(pop)
}

#include "details/DebugPacketWriter.hpp"
#include "details/DebugPacketReader.hpp"
