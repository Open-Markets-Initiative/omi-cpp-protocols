#pragma once

#include "../definitions.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const PacketHeader* packet_header = nullptr;
    const MessageHeader* message_header = nullptr;

    std::uint16_t message_count = 0;
    std::uint16_t message_index = 0;
    char message_type = 0;
    std::uint16_t message_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(PacketHeader)) {
            current = end;
            message = nullptr;
            message_count = 0;
            return;
        }

        current = data;
        message = nullptr;

        packet_header = PacketHeader::parse(current);
        current += sizeof(PacketHeader);

        message_header = nullptr;
        message_index = 0;
        message_type = 0;
        message_length = 0;
        message_count = packet_header->message_count.get();
    }

    // next message
    bool next() {

        if (message_index >= message_count) {
            return false;
        }

        if (current + sizeof(MessageHeader) > end) {
            return false;
        }

        message_index++;

        message_header = MessageHeader::parse(current);
        message = current + sizeof(MessageHeader);

        message_type = message_header->message_type.get();
        message_length = message_header->message_length.get();

        current += message_length + 2;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        packet_header = nullptr;
        message_header = nullptr;

        message = nullptr;
        message_count = 0;
        message_index = 0;
        message_type = 0;
        message_length = 0;
    }
};
}
