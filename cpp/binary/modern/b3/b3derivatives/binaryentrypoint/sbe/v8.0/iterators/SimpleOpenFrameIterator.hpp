#pragma once

#include "../definitions.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {
// SimpleOpenFrameIterator
struct SimpleOpenFrameIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const SimpleOpenFramingHeader* simple_open_framing_header = nullptr;
    const MessageHeader* message_header = nullptr;
    std::uint16_t template_id = 0;
    std::uint16_t message_length = 0;
    const std::byte* message = nullptr;

    // initialize over reassembled byte stream
    void initialize(const std::byte* data, std::size_t bytes) {
        current = data;
        end = data + bytes;

        simple_open_framing_header = nullptr;
        message_header = nullptr;
        message = nullptr;
        template_id = 0;
        message_length = 0;
    }

    // next reassembled packet
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(SimpleOpenFramingHeader) + sizeof(MessageHeader) > end) {
            return false;
        }

        simple_open_framing_header = SimpleOpenFramingHeader::parse(current);
        message_header = MessageHeader::parse(current + sizeof(SimpleOpenFramingHeader));
        message = current + sizeof(SimpleOpenFramingHeader) + sizeof(MessageHeader);

        template_id = message_header->template_id.get();
        message_length = simple_open_framing_header->message_length.get();

        current += message_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        simple_open_framing_header = nullptr;
        message_header = nullptr;
        message = nullptr;
        template_id = 0;
        message_length = 0;
    }
};
}
