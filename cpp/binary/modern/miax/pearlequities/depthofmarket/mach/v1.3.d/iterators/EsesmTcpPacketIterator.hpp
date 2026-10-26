#pragma once

#include "../definitions.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {
// EsesmTcpPacketIterator
struct EsesmTcpPacketIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const EsesmPacketHeader* esesm_packet_header = nullptr;
    char esesm_packet_type = 0;
    std::uint16_t esesm_packet_length = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t bytes) {
        current = data;
        end = data + bytes;

        esesm_packet_header = nullptr;
        message = nullptr;
        esesm_packet_type = 0;
        esesm_packet_length = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(EsesmPacketHeader) > end) {
            return false;
        }

        esesm_packet_header = EsesmPacketHeader::parse(current);
        message = current + sizeof(EsesmPacketHeader);

        esesm_packet_type = esesm_packet_header->esesm_packet_type.get();
        esesm_packet_length = esesm_packet_header->esesm_packet_length.get();

        current += esesm_packet_length + 2;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        esesm_packet_header = nullptr;
        message = nullptr;
        esesm_packet_type = 0;
        esesm_packet_length = 0;
    }
};
}
