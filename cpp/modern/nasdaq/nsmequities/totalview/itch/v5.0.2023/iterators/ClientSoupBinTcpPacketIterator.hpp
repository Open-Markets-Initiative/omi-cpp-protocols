#pragma once

#include "../definitions.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {
// ClientSoupBinTcpPacketIterator
struct ClientSoupBinTcpPacketIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    char client_packet_type = 0;
    std::uint16_t packet_length = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t length) {
        current = data;
        end = data + length;

        message = nullptr;
        client_packet_type = 0;
        packet_length = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(ClientPacketHeader) > end) {
            return false;
        }

        const auto* client_packet_header = ClientPacketHeader::parse(current);
        message = current + sizeof(ClientPacketHeader);

        client_packet_type = client_packet_header->client_packet_type.get();
        packet_length = client_packet_header->packet_length.get();

        current += packet_length + 2;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        message = nullptr;
        client_packet_type = 0;
        packet_length = 0;
    }
};
}
