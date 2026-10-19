#pragma once

#include "../definitions.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {
// TcpPacketIterator
struct TcpPacketIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const TcpPacketHeader* tcp_packet_header = nullptr;
    char packet_type = 0;
    std::uint16_t packet_length = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t bytes) {
        current = data;
        end = data + bytes;

        tcp_packet_header = nullptr;
        message = nullptr;
        packet_type = 0;
        packet_length = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(TcpPacketHeader) > end) {
            return false;
        }

        tcp_packet_header = TcpPacketHeader::parse(current);
        message = current + sizeof(TcpPacketHeader);

        packet_type = tcp_packet_header->packet_type.get();
        packet_length = tcp_packet_header->packet_length.get();

        current += packet_length + 2;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        tcp_packet_header = nullptr;
        message = nullptr;
        packet_type = 0;
        packet_length = 0;
    }
};
}
