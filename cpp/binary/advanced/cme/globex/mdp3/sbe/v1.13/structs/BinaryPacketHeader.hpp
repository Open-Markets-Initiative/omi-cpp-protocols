#pragma once

#include <cstddef>
#include "../types/PacketSequenceNumber.hpp"
#include "../types/SendingTime.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)

struct binary_packet_header {

    sbe_mdp3::packet_sequence_number packet_sequence_number;
    sbe_mdp3::sending_time sending_time;

    // parse method
    static binary_packet_header* parse(std::byte* buffer) {
        return reinterpret_cast<binary_packet_header*>(buffer);
    }

    // parse method const
    static const binary_packet_header* parse(const std::byte* buffer) {
        return reinterpret_cast<const binary_packet_header*>(buffer);
    }
};

// layout verification
static_assert(offsetof(binary_packet_header, packet_sequence_number) == 0, "unexpected offset of binary_packet_header::packet_sequence_number");
static_assert(offsetof(binary_packet_header, sending_time) == 4, "unexpected offset of binary_packet_header::sending_time");
static_assert(sizeof(binary_packet_header) == 12, "unexpected sizeof binary_packet_header");

#pragma pack(pop)
}
