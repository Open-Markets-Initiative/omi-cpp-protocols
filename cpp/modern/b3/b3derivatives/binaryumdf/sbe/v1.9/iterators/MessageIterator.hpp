#pragma once

#include "../definitions.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const PacketHeader* packet_header = nullptr;

    std::uint16_t template_id = 0;
    std::uint16_t message_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(PacketHeader)) {
            current = end;
            message = nullptr;
            packet_header = nullptr;
            template_id = 0;
            message_length = 0;
            return;
        }

        packet_header = PacketHeader::parse(data);
        current = data + sizeof(PacketHeader);
        message = nullptr;

        template_id = 0;
        message_length = 0;
    }

    // next message
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(FramingHeader) + sizeof(MessageHeader) > end) {
            return false;
        }

        const auto* header = FramingHeader::parse(current);
        // the code sits in the header behind this one
        const auto* code = MessageHeader::parse(current + sizeof(FramingHeader));
        message = current + sizeof(FramingHeader) + sizeof(MessageHeader);

        template_id = code->template_id.get();
        message_length = header->message_length.get();

        current += message_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        packet_header = nullptr;
        message = nullptr;
        template_id = 0;
        message_length = 0;
    }
};
}
