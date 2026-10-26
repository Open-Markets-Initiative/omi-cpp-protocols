#pragma once

#include "../definitions.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2026 {
// ServerSoupBinTcpPacketIterator
struct ServerSoupBinTcpPacketIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const ServerPacketHeader* server_packet_header = nullptr;
    char server_packet_type = 0;
    std::uint16_t packet_length = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t bytes) {
        current = data;
        end = data + bytes;

        server_packet_header = nullptr;
        message = nullptr;
        server_packet_type = 0;
        packet_length = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(ServerPacketHeader) > end) {
            return false;
        }

        server_packet_header = ServerPacketHeader::parse(current);
        message = current + sizeof(ServerPacketHeader);

        server_packet_type = server_packet_header->server_packet_type.get();
        packet_length = server_packet_header->packet_length.get();

        current += packet_length + 2;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        server_packet_header = nullptr;
        message = nullptr;
        server_packet_type = 0;
        packet_length = 0;
    }
};
}
