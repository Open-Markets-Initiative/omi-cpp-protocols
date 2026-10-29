#pragma once

#include "../definitions.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {
// BodyMessageIterator
struct BodyMessageIterator {

    const std::byte* current = nullptr;
    const std::byte* end = nullptr;

    const BodyHeader* body_header = nullptr;

    char msg_type = 0;
    std::uint16_t msg_length = 0;
    const std::byte* message = nullptr;

    // initialize parser
    void initialize(const std::byte* data, std::size_t length) {

        end = data + length;

        if (length < sizeof(BodyHeader)) {
            current = end;
            message = nullptr;
            body_header = nullptr;
            msg_type = 0;
            msg_length = 0;
            return;
        }

        body_header = BodyHeader::parse(data);
        current = data + sizeof(BodyHeader);
        message = nullptr;

        msg_type = 0;
        msg_length = 0;
    }

    // next message
    bool next() {

        if (current >= end) {
            return false;
        }

        if (current + sizeof(BodyHeader) > end) {
            return false;
        }

        const auto* header = BodyHeader::parse(current);
        message = current + sizeof(BodyHeader);

        msg_type = header->msg_type.get();
        msg_length = header->msg_length.get();

        current += msg_length - 3;

        return true;
    }

    // reset iterator
    void reset() {
        current = nullptr;
        end = nullptr;

        body_header = nullptr;
        message = nullptr;
        msg_type = 0;
        msg_length = 0;
    }
};
}
