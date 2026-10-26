#pragma once

#include "../definitions.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {
// SesmTcpPacketIterator
struct SesmTcpPacketIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const SesmPacketHeader* sesm_packet_header = nullptr;
    char sesm_packet_type = 0;
    std::uint16_t sesm_packet_length = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t bytes) {
        current = data;
        end = data + bytes;

        sesm_packet_header = nullptr;
        message = nullptr;
        sesm_packet_type = 0;
        sesm_packet_length = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(SesmPacketHeader) > end) {
            return false;
        }

        sesm_packet_header = SesmPacketHeader::parse(current);
        message = current + sizeof(SesmPacketHeader);

        sesm_packet_type = sesm_packet_header->sesm_packet_type.get();
        sesm_packet_length = sesm_packet_header->sesm_packet_length.get();

        current += sesm_packet_length + 2;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        sesm_packet_header = nullptr;
        message = nullptr;
        sesm_packet_type = 0;
        sesm_packet_length = 0;
    }
};
}
