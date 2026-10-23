#pragma once

#include "../definitions.hpp"

namespace cme::mdp3::v13 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const BinaryPacketHeader* binary_packet_header = nullptr;

    std::uint16_t schema_id = 0;
    std::uint16_t template_id = 0;
    std::uint16_t message_size = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(BinaryPacketHeader)) {
            current = end;
            message = nullptr;
            binary_packet_header = nullptr;
            schema_id = 0;
            template_id = 0;
            message_size = 0;
            return;
        }

        binary_packet_header = BinaryPacketHeader::parse(data);
        current = data + sizeof(BinaryPacketHeader);
        message = nullptr;

        schema_id = 0;
        template_id = 0;
        message_size = 0;
    }

    // next message
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(Message) > end) {
            return false;
        }

        const auto* header = Message::parse(current);
        message = current + sizeof(Message);

        schema_id = header->message_header.schema_id.get();
        template_id = header->message_header.template_id.get();
        message_size = header->message_size.get();

        current += message_size;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        binary_packet_header = nullptr;
        message = nullptr;
        schema_id = 0;
        template_id = 0;
        message_size = 0;
    }
};
}
