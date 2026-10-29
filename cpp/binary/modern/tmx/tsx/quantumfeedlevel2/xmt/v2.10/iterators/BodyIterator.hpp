#pragma once

#include "../definitions.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {
// BodyIterator
struct BodyIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const FrameHeader* frame_header = nullptr;
    const BodyHeader* body_header = nullptr;

    std::uint8_t num_body = 0;
    std::uint8_t message_index = 0;
    char msg_type = 0;
    std::uint16_t msg_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(FrameHeader)) {
            current = end;
            message = nullptr;
            num_body = 0;
            return;
        }

        current = data;
        message = nullptr;

        frame_header = FrameHeader::parse(current);
        current += sizeof(FrameHeader);

        body_header = nullptr;
        message_index = 0;
        msg_type = 0;
        msg_length = 0;
        num_body = frame_header->num_body.get();
    }

    // next message
    bool next() {

        if (message_index >= num_body) {
            return false;
        }

        if (current + sizeof(BodyHeader) > end) {
            return false;
        }

        message_index++;

        body_header = BodyHeader::parse(current);
        message = current + sizeof(BodyHeader);

        msg_type = body_header->msg_type.get();
        msg_length = body_header->msg_length.get();

        current += msg_length;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        frame_header = nullptr;
        body_header = nullptr;

        message = nullptr;
        num_body = 0;
        message_index = 0;
        msg_type = 0;
        msg_length = 0;
    }
};
}
