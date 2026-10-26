#pragma once

#include "../definitions.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const PacketHeader* packet_header = nullptr;
    const MessageHeader* message_header = nullptr;

    std::uint8_t number_msgs = 0;
    std::uint8_t message_index = 0;
    std::uint16_t message_type = 0;
    std::uint16_t message_size = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(PacketHeader)) {
            current = end;
            message = nullptr;
            number_msgs = 0;
            return;
        }

        current = data;
        message = nullptr;

        packet_header = PacketHeader::parse(current);
        current += sizeof(PacketHeader);

        message_header = nullptr;
        message_index = 0;
        message_type = 0;
        message_size = 0;
        number_msgs = packet_header->number_msgs.get();
    }

    // next message
    bool next() {

        if (message_index >= number_msgs) {
            return false;
        }

        if (current + sizeof(MessageHeader) > end) {
            return false;
        }

        message_index++;

        message_header = MessageHeader::parse(current);
        message = current + sizeof(MessageHeader);

        message_type = message_header->message_type.get();
        message_size = message_header->message_size.get();

        current += message_size;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        packet_header = nullptr;
        message_header = nullptr;

        message = nullptr;
        number_msgs = 0;
        message_index = 0;
        message_type = 0;
        message_size = 0;
    }
};
}
