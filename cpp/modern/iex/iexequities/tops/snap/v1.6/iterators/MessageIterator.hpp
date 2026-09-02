#pragma once

#include "../definitions.hpp"

namespace iex::iexequities::tops::snap::v1_6 {
// MessageIterator
struct MessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    char message_type = 0;
    std::uint16_t message_length = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t length) {
        current = data;
        end = data + length;

        message = nullptr;
        message_type = 0;
        message_length = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(MessageHeader) > end) {
            return false;
        }

        const auto* message_header = MessageHeader::parse(current);
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

        message = nullptr;
        message_type = 0;
        message_length = 0;
    }
};
}
