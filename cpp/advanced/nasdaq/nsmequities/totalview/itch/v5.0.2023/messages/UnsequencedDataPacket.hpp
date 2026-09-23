#pragma once

#include <cstddef>
#include "../structs/ClientPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/UnsequencedMessageType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;


#pragma pack(push, 1)

// Unsequenced Data Packet
struct unsequenced_data_packet {

    struct fields_type {
        itch_totalview::unsequenced_message_type unsequenced_message_type;
    };

    client_packet_header header = {std::uint16_t(sizeof(client_packet_header) + sizeof(fields_type) - 2), client_packet_type::enum_type::unsequenced_data_packet};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(client_packet_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.packet_length.get().value();
        return (sz + 2) == sizeof(client_packet_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(client_packet_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_var_data unsequenced_message() const {
        return { tail_begin(), static_cast<std::size_t>(header.packet_length.get().value() - 2), tail_end() };
    }


    // parse method
    static unsequenced_data_packet* parse(std::byte* buffer) {
        return reinterpret_cast<unsequenced_data_packet*>(buffer);
    }

    // parse method const
    static const unsequenced_data_packet* parse(const std::byte* buffer) {
        return reinterpret_cast<const unsequenced_data_packet*>(buffer);
    }

};

// layout verification
static_assert(offsetof(unsequenced_data_packet::fields_type, unsequenced_message_type) == 0, "unexpected offset of unsequenced_data_packet::fields_type::unsequenced_message_type");
static_assert(sizeof(unsequenced_data_packet::fields_type) == 1, "unexpected sizeof unsequenced_data_packet::fields_type");

#pragma pack(pop)
}

#include "details/UnsequencedDataPacketWriter.hpp"
#include "details/UnsequencedDataPacketReader.hpp"
