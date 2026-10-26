#pragma once

#include "../definitions.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const PacketHeader* packet_header = nullptr;
    const MessageHeader* message_header = nullptr;

    std::uint8_t message_count = 0;
    std::uint8_t message_index = 0;
    char message_type = 0;
    std::uint8_t tag_length = 0;
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
        tag_length = 0;
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
        tag_length = message_header->tag_length.get();

        current += tag_length + 1;

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
        tag_length = 0;
    }
};
}
