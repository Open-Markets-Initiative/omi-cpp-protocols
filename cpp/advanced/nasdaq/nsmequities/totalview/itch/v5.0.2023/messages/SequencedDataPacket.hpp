#pragma once

#include <cstddef>
#include "../structs/ServerPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SequencedMessageType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v5_0_2023;


#pragma pack(push, 1)

// Sequenced Data Packet
struct sequenced_data_packet {

    struct fields_type {
        itch_totalview::sequenced_message_type sequenced_message_type;
    };

    server_packet_header header = {std::uint16_t(sizeof(server_packet_header) + sizeof(fields_type) - 2), server_packet_type::enum_type::sequenced_data_packet};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(server_packet_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.packet_length.get().value();
        return (sz + 2) == sizeof(server_packet_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + ((sz + 2) - sizeof(server_packet_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    external_var_data sequenced_message() const {
        return { tail_begin(), static_cast<std::size_t>(header.packet_length.get().value() - 2), tail_end() };
    }


    // parse method
    static sequenced_data_packet* parse(std::byte* buffer) {
        return reinterpret_cast<sequenced_data_packet*>(buffer);
    }

    // parse method const
    static const sequenced_data_packet* parse(const std::byte* buffer) {
        return reinterpret_cast<const sequenced_data_packet*>(buffer);
    }

};

// layout verification
static_assert(offsetof(sequenced_data_packet::fields_type, sequenced_message_type) == 0, "unexpected offset of sequenced_data_packet::fields_type::sequenced_message_type");
static_assert(sizeof(sequenced_data_packet::fields_type) == 1, "unexpected sizeof sequenced_data_packet::fields_type");

#pragma pack(pop)
}

#include "details/SequencedDataPacketWriter.hpp"
#include "details/SequencedDataPacketReader.hpp"
